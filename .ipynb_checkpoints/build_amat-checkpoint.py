from pynestml.codegeneration.nest_code_generator_utils import NESTCodeGeneratorUtils

# Generate standard AMAT module into its own folder
NESTCodeGeneratorUtils.generate_code_for(
    "amat_neuron.nestml",
    target_path="benchmark/Running/targets_amat/target",
    module_name="nestml_amat_module",
    logging_level="WARNING"
)
print("AMAT NESTML module successfully built.")

# Generate CSE optimized AMAT module into a separate folder
NESTCodeGeneratorUtils.generate_code_for(
    "amat_neuron_cse.nestml",
    target_path="benchmark/Running/targets_amat_cse/target",
    module_name="nestml_cse_amat_module",
    logging_level="WARNING"
)
print("AMAT NEST CSE Template successfully built for CSE optimisation.")
