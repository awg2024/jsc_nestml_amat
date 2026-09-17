import matplotlib.pyplot as plt
import nest
import numpy as np

nest.set_verbosity("M_WARNING")

simtime = 1000
dcfrom, dcstep, dcto = 0, 20, 2000
h = 0.1

def run_fi_curve(model_name, module_to_install=None, model_params=None):
    nest.ResetKernel()
    nest.resolution = h

    if module_to_install is not None:
        nest.Install(module_to_install)

    neuron = nest.Create(model_name, params=model_params or {})
    sr = nest.Create("spike_recorder")
    sr.record_to = "memory"
    nest.Connect(neuron, sr, syn_spec={"weight": 1.0, "delay": h})

    n_data = int(dcto / float(dcstep))
    amplitudes = np.zeros(n_data)
    event_freqs = np.zeros(n_data)

    for i, amp in enumerate(range(dcfrom, dcto, dcstep)):
        neuron.I_e = float(amp)
        nest.Simulate(1000)  # settle

        t_start = nest.biological_time
        nest.Simulate(simtime)
        t_end = nest.biological_time

        spike_times = np.array(sr.events["times"])
        n_events = np.sum((spike_times >= t_start) & (spike_times < t_end))

        amplitudes[i] = amp
        event_freqs[i] = n_events / (simtime / 1000.0)
        print(f"[{model_name}] I_e={amp} pA -> {event_freqs[i]:.1f} Hz")

    return amplitudes, event_freqs


amp_native, freq_native = run_fi_curve("hh_psc_alpha") # NEST 
amp_nestml, freq_nestml = run_fi_curve("hh_psc_alpha",  module_to_install="/p/project1/paj2623/gray2/benchmark/Running/targets_hh/target/nestml_hh_module.so") # NESTML 


plt.plot(amp_native, freq_native, label="aeif_psc_alpha", marker=".")
plt.plot(amp_nestml, freq_nestml, label="aeif_psc_alpha_neuron_nestml", marker=".")
plt.xlabel("I_e (pA)")
plt.ylabel("Firing rate (Hz)")
plt.legend()
plt.title("f-I curve: native vs NESTML")
plt.savefig("fi_curve.png")
plt.show()