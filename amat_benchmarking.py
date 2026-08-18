import sys
import json
import time
import os 
from dataclasses import dataclass, replace
import nest
import numpy as np

@dataclass(frozen=True)
class AMATConfig:

    pulse_times_ms: tuple[float, ...] = (10.0, 30.0, 210.0, 270.0)
    pulse_amplitude_pa: float = 1000.0
    pulse_width_ms: float = 1.0
    simulation_time_ms: float = 400.0

    first_pulse_ms: float = 10.0
    response_window_ms: float = 50.0

    tau_m_ms: float = 10.0
    C_m_pf: float = 200.0
    t_ref_ms: float = 2.0
    E_L_mv: float = -70.0
    resting_threshold_mv: float = -65.0

    tau_syn_ex_ms: float = 1.0
    tau_syn_in_ms: float = 3.0
    tau_1_ms: float = 10.0
    tau_2_ms: float = 200.0

    alpha_1_mv: float = 10.0
    alpha_2_mv: float = 0.0
    gamma: float = 1.5
    B: float = 4.0

    g: float = 5.0
    balanced_simtime: float = 3000.0
    delay: float = 1.0
    eta: float = 1.5
    epsilon: float = 0.1
    order: int = 500
    J_ex: float = 0.15
    n_record: int = 100

    I_e_pa: float = 0.0
    resolution: float = 0.1

    @property
    def J_in(self):
        return self.g * self.J_ex


NESTML_MODEL = "amat_neuron_nestml"
NEST_MODEL = "amat2_psc_exp"
NESTML_MODULE = "nestml_amat_module"


def exp_psp_norm(tau_m, C_m, tau_syn):

    if np.isclose(tau_m, tau_syn):
        return tau_m / (np.e * C_m)

    t_peak = (
        tau_m
        * tau_syn
        / (tau_m - tau_syn)
        * np.log(tau_m / tau_syn)
    )

    return (
        tau_m
        * tau_syn
        / (C_m * (tau_m - tau_syn))
        * (
            np.exp(-t_peak / tau_m)
            - np.exp(-t_peak / tau_syn)
        )
    )


def run_balanced_network(model_name, order_val, input_type):

    config = AMATConfig()

    NE = 4 * order_val
    NI = order_val
    N_total = NE + NI

    CE = int(config.epsilon * NE)
    CI = int(config.epsilon * NI)

    N_rec = min(config.n_record, NE, NI)

    norm_ex = exp_psp_norm(
        config.tau_m_ms,
        config.C_m_pf,
        config.tau_syn_ex_ms,
    )


    # Add a scaling factor right below where CE and CI are defined
    scaling_factor = np.sqrt(50.0 / order_val) # Normalises background input variance
    
    J_ex = (config.J_ex / norm_ex) * scaling_factor

    delta_V = (
        config.resting_threshold_mv
        - config.E_L_mv
    )

    baseline_current = (
        delta_V
        * config.C_m_pf
        / config.tau_m_ms
    )

    baseline_rate_hz = (
        1000.0
        * baseline_current
        / (
            J_ex
            * config.tau_syn_ex_ms
        )
    )

    external_rate_hz = (
        config.eta
        * baseline_rate_hz
    )

    if input_type == "inh_push":
        config = replace(
            config,
            g=config.g * 2.0,
        )

    elif input_type == "exc_push":
        config = replace(
            config,
            g=config.g * 0.5,
        )

        external_rate_hz *= 1.75

    J_in = -config.g * J_ex

    nest.ResetKernel()

    nest.resolution = config.resolution
    nest.rng_seed = 12345
    nest.print_time = False
    nest.set_verbosity("M_ERROR")

    threads = int(
        os.environ.get(
            "SLURM_CPUS_PER_TASK",
            1,
        )
    )

    nest.local_num_threads = threads
    nest.Install(NESTML_MODULE)

    if model_name not in nest.node_models:
        raise RuntimeError(
            f"Model '{model_name}' is not available."
        )

    n_processes = nest.NumProcesses()
    n_threads = nest.local_num_threads

    neuron_params = {
        "tau_m": config.tau_m_ms,
        "C_m": config.C_m_pf,
        "E_L": config.E_L_mv,
        "alpha_1": config.alpha_1_mv,
        "alpha_2": config.alpha_2_mv,
    }

    start_build = time.perf_counter()

    neurons_ex = nest.Create(
        model_name,
        NE,
        params=neuron_params,
    )

    neurons_in = nest.Create(
        model_name,
        NI,
        params=neuron_params,
    )

    neurons = neurons_ex + neurons_in

    noise = nest.Create(
        "poisson_generator",
        params={
            "rate": external_rate_hz
        },
    )

    spikes_ex = nest.Create(
        "spike_recorder"
    )

    spikes_in = nest.Create(
        "spike_recorder"
    )

    nest.Connect(
        noise,
        neurons,
        syn_spec={
            "weight": J_ex,
            "delay": config.delay,
        },
    )

    nest.Connect(
        neurons_ex[:N_rec],
        spikes_ex,
    )

    nest.Connect(
        neurons_in[:N_rec],
        spikes_in,
    )

    nest.Connect(
        neurons_ex,
        neurons,
        conn_spec={
            "rule": "fixed_indegree",
            "indegree": CE,
        },
        syn_spec={
            "weight": J_ex,
            "delay": config.delay,
        },
    )

    nest.Connect(
        neurons_in,
        neurons,
        conn_spec={
            "rule": "fixed_indegree",
            "indegree": CI,
        },
        syn_spec={
            "weight": J_in,
            "delay": config.delay,
        },
    )

    build_time = (
        time.perf_counter()
        - start_build
    )

    start_sim = time.perf_counter()

    nest.Simulate(
        config.balanced_simtime
    )

    simulation_time = (
        time.perf_counter()
        - start_sim
    )

    events_ex = int(
        spikes_ex.n_events
    )

    events_in = int(
        spikes_in.n_events
    )

    rate_ex = (
        events_ex
        * 1000.0
        / (
            config.balanced_simtime
            * N_rec
        )
    )

    rate_in = (
        events_in
        * 1000.0
        / (
            config.balanced_simtime
            * N_rec
        )
    )

    return {
        "model": model_name,
        "input_type": input_type,
        "order": order_val,
        "mpi_processes": int(n_processes),
        "threads_per_process": int(n_threads),
        "total_cores": int(
            n_processes
            * n_threads
        ),
        "total_neurons": int(N_total),
        "total_synapses": int(
            N_total
            * (CE + CI)
        ),
        "build_time_s": float(
            build_time
        ),
        "simulation_time_s": float(
            simulation_time
        ),
        "total_wall_clock_s": float(
            build_time
            + simulation_time
        ),
        "total_spikes_captured": int(
            events_ex
            + events_in
        ),
        "exc_rate_hz": float(
            rate_ex
        ),
        "inh_rate_hz": float(
            rate_in
        ),
    }


def main():

    if len(sys.argv) != 3:
        print(
            "Usage: "
            "python amat_benchmarking.py "
            "<static|exc_push|inh_push> "
            "<order>"
        )
        sys.exit(1)

    input_type = sys.argv[1]
    order_val = int(sys.argv[2])

    valid_modes = {"static","exc_push","inh_push"}
    if input_type not in valid_modes:
        raise ValueError(f"Unknown input type: {input_type}")

    if nest.Rank() != 0:
        sys.stdout = open(os.devnull, 'w')
        sys.stderr = open(os.devnull, 'w')
    
    nestml_results = (
        run_balanced_network(
            NESTML_MODEL,
            order_val,
            input_type,
        )
    )

    nest_results = (
        run_balanced_network(
            NEST_MODEL,
            order_val,
            input_type))

    # Change this part in your main() function:
    # Only Rank 0 prints the final clean results
    if nest.Rank() == 0:
        # Restore stdout just in case it was modified
        sys.stdout = sys.__stdout__ 
        

        print("benchmarking results") 
        print(f"Input type : {input_type}")
        print(f"Order      : {order_val}")
        print(f"NESTML Model Build Time : {nestml_results['build_time_s']:.4f} seconds")
        print(f"Native NEST Build Time   : {nest_results['build_time_s']:.4f} seconds")

    
         

if __name__ == "__main__":
    main()