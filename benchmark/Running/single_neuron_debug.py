"""
single_neuron_beta_sweep.py

Isolates ONE amat neuron (nestml or nestml_cse or the native amat2_psc_exp),
driven ONLY by the same external Poisson rate the full brunel network uses
-- no recurrent connections at all -- and sweeps beta.

This tells you whether the 0 Hz -> 170 Hz jump you're seeing is:
  (a) a property of the single neuron / ODE integration itself, or
  (b) an emergent effect of the recurrent network (avalanche/bistability).

Usage (run once per beta value and compare):
    python3 single_neuron_beta_sweep.py --simulated_neuron amat_nestml --beta 0.0
    python3 single_neuron_beta_sweep.py --simulated_neuron amat_nestml --beta 0.5
    python3 single_neuron_beta_sweep.py --simulated_neuron amat_nestml --beta 1.0
    python3 single_neuron_beta_sweep.py --simulated_neuron amat_nestml --beta 2.0
    python3 single_neuron_beta_sweep.py --simulated_neuron amat_nestml --beta 3.0
    python3 single_neuron_beta_sweep.py --simulated_neuron amat_nestml --beta 4.0

Or just loop over all of them in one process (see __main__ at bottom) to get
a table in one shot.
"""
import argparse
import numpy as np
import scipy.special as sp
import nest

MODEL_VARIANTS = {
    "amat_nestml":     {"module": "nestml_amat_module",     "model": "amat_neuron_nestml"},
    "amat_nestml_cse": {"module": "nestml_amat_cse_module", "model": "amat_neuron_nestml"},
    "amat2_psc_exp":   {"module": None,                     "model": "amat2_psc_exp"},
}


def exp_psp_norm(tau_m, C_m, tau_syn):
    if np.isclose(tau_m, tau_syn):
        return tau_m / (np.e * C_m)
    t_peak = tau_m * tau_syn / (tau_m - tau_syn) * np.log(tau_m / tau_syn)
    return (
        tau_m * tau_syn / (C_m * (tau_m - tau_syn))
        * (np.exp(-t_peak / tau_m) - np.exp(-t_peak / tau_syn))
    )


def run_one(simulated_neuron, beta, eta=0.8, target_psp=0.15, simtime=2000.0):
    variant = MODEL_VARIANTS[simulated_neuron]

    nest.ResetKernel()
    nest.resolution = 0.01
    if variant["module"] is not None:
        nest.Install(variant["module"])

    common_params = {
        "tau_m": 10.0, "C_m": 200.0, "E_L": -70.0,
        "tau_1": 10.0, "tau_2": 200.0,
        "alpha_1": 10.0, "alpha_2": 0.0,
        "omega": -65.0, "tau_v": 5.0,
        "beta": beta, "I_e": 0.0,
    }
    if simulated_neuron == "amat2_psc_exp":
        neuron_params = {**common_params, "tau_syn_ex": 1.0, "tau_syn_in": 3.0, "t_ref": 2.0}
    else:
        neuron_params = {**common_params, "tau_syn_exc": 1.0, "tau_syn_inh": 3.0, "refr_T": 2.0}

    neuron = nest.Create(variant["model"], 1, params=neuron_params)

    # --- reproduce the exact external-drive formula used in brunel_alpha_nest.py ---
    tauMem, CMem, tauSynEx = 10.0, 200.0, 1.0
    E_L, omega = -70.0, -65.0
    norm_ex = exp_psp_norm(tauMem, CMem, tauSynEx)
    J_ex = target_psp / norm_ex
    baseline_current = (omega - E_L) * CMem / tauMem
    p_rate = eta * 1000.0 * baseline_current / (J_ex * tauSynEx)

    noise = nest.Create("poisson_generator", params={"rate": p_rate})
    nest.CopyModel("static_synapse", "ext_exc", {"weight": J_ex, "delay": 1.5})
    nest.Connect(noise, neuron, syn_spec="ext_exc")

    # record whatever's available -- V_th tells you directly if threshold is
    # behaving (rising with depolarization) or misbehaving (dropping/blowing up)
    recordables = nest.GetDefaults(variant["model"]).get("recordables", [])
    record_from = [r for r in ["V_m", "V_th"] if r in recordables] or ["V_m"]
    mm = nest.Create("multimeter", params={"record_from": record_from, "interval": 0.1})
    nest.Connect(mm, neuron)

    spikes = nest.Create("spike_recorder")
    nest.Connect(neuron, spikes)

    nest.Simulate(simtime)

    n_spikes = spikes.n_events
    rate_hz = n_spikes / simtime * 1000.0

    ev = mm.get("events")
    diagnostics = {}
    for r in record_from:
        v = np.asarray(ev[r])
        diagnostics[r] = {
            "min": float(np.nanmin(v)),
            "max": float(np.nanmax(v)),
            "mean": float(np.nanmean(v)),
            "has_nan": bool(np.isnan(v).any()),
        }

    return rate_hz, n_spikes, p_rate, diagnostics


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--simulated_neuron", default="amat_nestml",
                         choices=list(MODEL_VARIANTS.keys()))
    parser.add_argument("--betas", type=float, nargs="+",
                         default=[0.0, 0.5, 1.0, 2.0, 3.0, 4.0])
    parser.add_argument("--eta", type=float, default=0.8)
    parser.add_argument("--target_psp", type=float, default=0.15)
    parser.add_argument("--simtime", type=float, default=2000.0)
    args = parser.parse_args()

    print(f"model={args.simulated_neuron}  eta={args.eta}  target_psp={args.target_psp}")
    print("-" * 70)
    for beta in args.betas:
        rate_hz, n_spikes, p_rate, diag = run_one(
            args.simulated_neuron, beta, args.eta, args.target_psp, args.simtime
        )
        print(f"beta={beta:>5.2f} | p_rate={p_rate:8.2f} Hz | "
              f"firing_rate={rate_hz:8.2f} Hz | n_spikes={n_spikes}")
        for r, d in diag.items():
            print(f"    {r}: min={d['min']:8.2f}  max={d['max']:8.2f}  "
                  f"mean={d['mean']:8.2f}  has_nan={d['has_nan']}")
        print()