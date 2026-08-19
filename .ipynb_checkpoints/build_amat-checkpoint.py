from pynestml.codegeneration.nest_code_generator_utils import NESTCodeGeneratorUtils

# DEFINITION ON THE FOLLOW NEURONAL MODELS across CSE Implementations 
# targets_amat = baseline testing (BASELINE)
# targets_amat_coeff = precompute coeffients (PATCH 1) 
# targets_amat_vm_tmp = replace only v_m_tmp (PATCH 2)
# target_amat_all_tmp = replace common coefficient alpha1, alpha2, v_m_tmp (PATCH 3) 

# BASELINE 
NESTCodeGeneratorUtils.generate_code_for(
    "amat_neuron.nestml",
    target_path="benchmark/Running/targets_amat/target",
    module_name="nestml_amat_module",
    logging_level="WARNING"
)
print("AMAT NESTML module successfully built.")

# PATCH 1 
NESTCodeGeneratorUtils.generate_code_for(
    "amat_neuron_cse.nestml",
    target_path="benchmark/Running/targets_amat_coeff/target",
    module_name="nestml_cse_coeff_amat_module",
    logging_level="WARNING"
)
print("AMAT NEST CSE Patch 1.")

# PATCH 2 
NESTCodeGeneratorUtils.generate_code_for(
    "amat_neuron_cse.nestml",
    target_path="benchmark/Running/targets_amat_vm_tmp/target",
    module_name="nestml_cse_amat_module",
    logging_level="WARNING"
)
print("AMAT NEST CSE Patch 2.")

# PATCH 3 
NESTCodeGeneratorUtils.generate_code_for(
    "amat_neuron_cse.nestml",
    target_path="benchmark/Running/targets_amat_all_tmp/target",
    module_name="nestml_cse_amat_module",
    logging_level="WARNING"
)
print("AMAT NEST CSE Patch 3.")
