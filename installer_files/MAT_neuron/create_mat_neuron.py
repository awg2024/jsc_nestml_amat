#!/usr/bin/env python
import os
from pynestml.frontend.pynestml_frontend import generate_nest_target

current_dir = os.path.dirname(
    os.path.abspath(__file__)
)


input_path = os.path.join(
    current_dir,
    "mat2_psc_exp_neuron.nestml"
)


target_path = os.path.join(
    current_dir,
    "mat_component"
)


os.makedirs(
    target_path,
    exist_ok=True
)

# Generate NEST module
generate_nest_target(
    input_path=input_path,
    target_path=target_path,
    logging_level="INFO",
    module_name="nestml_mat_module",
    suffix="_mat_nestml"
)

print("\n[MESSAGE] MAT neuron generation complete.")
print(f"Input : {input_path}")
print(f"Output: {target_path}")