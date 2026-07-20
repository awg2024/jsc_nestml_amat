#!/usr/bin/env python

import matplotlib.pyplot as plt
import nest
import numpy as np
import os
from pynestml.frontend.pynestml_frontend import generate_nest_target

# Your NESTML model file
neuron_model = "amat_neuron"
input_path = os.path.join(
    neuron_model + ".nestml"
)

# Where generated C++ code/module will be placed
target_path = os.path.join(
    neuron_model + "_module"
)

# Generate NEST module
generate_nest_target(
    input_path=input_path,
    target_path=target_path,
    module_name="amat_module",
    suffix="_nestml",
    logging_level="DEBUG"
)

print("AMAT NESTML generation complete.")