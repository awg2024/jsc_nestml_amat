#!/usr/bin/env python3
import argparse
import json
import time
import nest

def main():
    parser = argparse.ArgumentParser()

    parser.add_argument("--model", required=True, help='HH or AMAT')
    parser.add_argument("--enable_cse", required=True, help='True or False')

    parser.add_argument("--neurons",type=int,default=20000)
    parser.add_argument("--warmup-ms",type=float,default=100.0)
    parser.add_argument("--sim-ms",type=float,default=1000.0,)
    parser.add_argument("--resolution",type=float,default=0.1,)
    parser.add_argument("--params",type=str,default="{}",help='JSON dictionary, e.g. \'{"I_e": 500.0}\'',)

    args = parser.parse_args()
    params = json.loads(args.params)
    nest.ResetKernel()
    nest.SetKernelStatus({
        "local_num_threads": 1,
        "resolution": args.resolution,
    })


    if args.model == "AMAT":
        neuron_model = "amat_neuron_nestml"

        if args.enable_cse == "True":
            module_name = "nestml_amat_cse_module"
            nest.Install(module_name)
            neurons = nest.Create(neuron_model, args.neurons)
        
        elif args.enable_cse == "False":
            module_name = "nestml_amat_module"
            nest.Install(module_name)
            neurons = nest.Create(neuron_model, args.neurons)
    
    elif args.model == "HH":
        neuron_model = "hh_psc_alpha_custom_nestml"
        
        if args.enable_cse == "True":
            module_name = "/p/project1/paj2623/gray2/benchmark/Running/targets_hh_optimised_cse/target/nestml_hh_cse_module.so"
            nest.Install(module_name)
            neurons = nest.Create(neuron_model, args.neurons)

        elif args.enable_cse == "False":
            module_name = "/p/project1/paj2623/gray2/benchmark/Running/targets_hh_optimised_cse/target/nestml_hh_module.so"
            nest.Install(module_name)
            neurons = nest.Create(neuron_model, args.neurons)
    else:
        raise ValueError(f"Unknown model: {args.model}")

    if params:
        nest.SetStatus(
            neurons,
            params,
        )

    #
    # First Simulate() may contain preparation/setup work.
    #
    nest.Simulate(
        args.warmup_ms
    )

    #
    # Measure second Simulate() only.
    #
    wall_start = time.perf_counter()

    nest.Simulate(
        args.sim_ms
    )

    wall_end = time.perf_counter()

    status = nest.GetKernelStatus()

    interesting_keys = [
        "time_simulate",
        "time_simulate_cpu",
        "time_update",
        "time_update_cpu",
        "time_gather_spike_data",
        "time_deliver_spike_data",
        "time_communicate_spike_data",
        "time_communicate_prepare",
        "local_spike_counter",
        "biological_time",
    ]

    result = {
        "module": module_name,
        "model": neuron_model,
        "neurons": args.neurons,
        "sim_ms": args.sim_ms,
        "wall_clock_python": (
            wall_end - wall_start
        ),
    }

    for key in interesting_keys:
        if key in status:
            result[key] = status[key]

    print(
        json.dumps(
            result,
            indent=2,
            sort_keys=True,
        )
    )


if __name__ == "__main__":
    main()