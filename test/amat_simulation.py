import nest
import matplotlib.pyplot as plt

nest.ResetKernel()

nest.SetKernelStatus({
    "resolution": 0.1,
    "rng_seed": 12345
})

nest.Install("amat_module")

MODEL = "YOUR_GENERATED_MODEL_NAME"

print("Available models:")
print([m for m in nest.Models() if "amat" in m.lower()])

neuron = nest.Create(MODEL)

print(nest.GetDefaults(MODEL)["recordables"])

dc = nest.Create("dc_generator", {"amplitude": 400.0})

voltmeter = nest.Create("voltmeter")

voltmeter.set({
    "interval": 0.1,
    "record_from": nest.GetDefaults(MODEL)["recordables"]
})

spikes = nest.Create("spike_recorder")

nest.Connect(dc, neuron)
nest.Connect(voltmeter, neuron)
nest.Connect(neuron, spikes)

nest.Simulate(1000.)

events = voltmeter.get("events")

for variable in nest.GetDefaults(MODEL)["recordables"]:
    plt.figure()
    plt.plot(events["times"], events[variable])
    plt.title(variable)
    plt.xlabel("Time (ms)")

plt.show()