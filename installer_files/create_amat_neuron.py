#!/usr/bin/env python

import matplotlib.pyplot as plt
import nest
import numpy as np
import os
from pynestml.frontend.pynestml_frontend import generate_nest_target

# Downloading the nestml MAT neuronal model from nestml 
# Link to the repo is found below
# # https://github.com/nest/nestml/blob/main/models/neurons/mat2_psc_exp_neuron.nestml 


# neuron_model = "mat"
# files = [os.path.join("models", "neurons", neuron_model + ".nestml")]
# input_path = "/opt/miniconda3/envs/als_nestml/models/neurons/mat2_psc_exp_neuron.nestml"

# generate_nest_target(input_path=input_path,
#                      target_path="/opt/miniconda3/envs/als_nestml/models/mat_component",
#                      logging_level="DEBUG",
#                      module_name="nestml_mat_module",
#                      suffix="_mat_nestml")

