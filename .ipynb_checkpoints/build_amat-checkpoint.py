from pynestml.codegeneration.nest_code_generator_utils import (
    NESTCodeGeneratorUtils
)

NESTCodeGeneratorUtils.generate_code_for(
    "amat_neuron.nestml",
    module_name="nestml_amat_module",
    logging_level="WARNING",
)

print("AMAT NESTML module successfully built.")