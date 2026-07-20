import nest
import matplotlib.pyplot as plt

nest.ResetKernel()
nest.set_verbosity("M_ERROR")

nest.SetKernelStatus({
    "resolution":0.1,
    "local_num_threads":1,
    "rng_seed":12345
})

nest.Install("amat_module")

print("MAT model loaded:",
      "amat_neuron_nestml" in nest.Models())

neuron = nest.Create("amat_neuron_nestml")

print(f"AMAT neuronal parameters: {neuron.get()}")

dc = nest.Create(
    "dc_generator",
    {"amplitude":400.0}
)


nest.Connect(dc, neuron)

voltmeter = nest.Create(
    "voltmeter"
)

voltmeter.set(
    {
        "interval": 0.1,
        "record_from": [
            "V_m",
        ]
    }
)

spikedetector = nest.Create("spike_recorder")


# Correct direction
nest.Connect(voltmeter, neuron)
nest.Connect(neuron, spikedetector)


nest.Simulate(1000.0)

events = voltmeter.get("events")

t = events["times"]
V = events["V_m"]
theta = events["V_th"]

fig, ax = plt.subplots(2, 1, sharex=True)

ax[0].plot(t, V)
ax[0].set_ylabel("V_m (mV)")

ax[1].plot(t, theta)
ax[1].set_ylabel("V_th (mV)")
ax[1].set_xlabel("Time (ms)")
plt.legend()
plt.show()
