from pynestml.codegeneration.nest_code_generator_utils import NESTCodeGeneratorUtils

# BASELINE 
#NESTCodeGeneratorUtils.generate_code_for(
#    "amat_neuron.nestml",
#    target_path="benchmark/Running/targets_amat/target",
#    module_name="nestml_amat_module",
#    logging_level="WARNING"
#)
#print("AMAT NESTML module successfully built.")

# PATCH 1 
NESTCodeGeneratorUtils.generate_code_for(
    "amat_neuron_cse.nestml",
    target_path="benchmark/Running/targets_amat_optimised_cse/target",
    module_name="nestml_amat_cse_module",
    logging_level="WARNING"
)
print("AMAT NEST CSE template for optimisation.")
