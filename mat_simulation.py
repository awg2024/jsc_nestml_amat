import nest
import numpy as np
import matplotlib.pyplot as plt
import sys 

# This is a script creating and testing the MAT neuronal model 
# Here we attempt to recreate the findings displayed in the model paper Yamauchi et al., 2011
# https://www.frontiersin.org/journals/computational-neuroscience/articles/10.3389/fncom.2011.00042/full


nest.ResetKernel()
nest.set_verbosity("M_ERROR")

nest.SetKernelStatus({
    "resolution":0.1,
    "local_num_threads":1,
    "rng_seed":12345
})


nest.Install("nestml_mat_module")


print("MAT model loaded:",
      "mat2_psc_exp" in nest.Models())


neuron = nest.Create("mat2_psc_exp")

print(neuron.get())

dc = nest.Create(
    "dc_generator",
    {"amplitude":500.0}
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
            "V_th"
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

plt.plot(t, V, label="V_m")
plt.plot(t, theta, label="Adaptive threshold")
plt.legend()
plt.show()

