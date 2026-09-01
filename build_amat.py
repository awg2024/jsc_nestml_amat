
# RE-RUNNING SCRIPT WILL OVER-WRITE THE .CPP CSE template. 

from pynestml.codegeneration.nest_code_generator_utils import NESTCodeGeneratorUtils

# nestml amat generation  
NESTCodeGeneratorUtils.generate_code_for(
   "amat_neuron.nestml",
   target_path="benchmark/Running/targets_amat/target",
   module_name="nestml_amat_module",
   logging_level="WARNING",
   codegen_opts={
    "enable_cse": False
   }
)
print("AMAT NESTML .cpp script produced!")

NESTCodeGeneratorUtils.generate_code_for(
   "amat_neuron_cse.nestml",
   target_path="benchmark/Running/targets_amat_optimised_cse/target",
   module_name="nestml_amat_cse_module",
   logging_level="WARNING",
   codegen_opts={
    "enable_cse": True
   }
)

print("AMAT NESTML CSE optimisation .cpp script produced!")
