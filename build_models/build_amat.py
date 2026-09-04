from pynestml.codegeneration.nest_code_generator_utils import NESTCodeGeneratorUtils
import os 

base_dir = "/p/project1/paj2623/gray2/benchmark/Running"

# build specific paths and mkdir 
amat_path = os.path.join(base_dir, "targets_amat/target")
amat_cse_path = os.path.join(base_dir, "targets_amat_optimised_cse/target")

os.makedirs(amat_path, exist_ok=True)
os.makedirs(amat_cse_path, exist_ok=True)


# nestml amat generation  
NESTCodeGeneratorUtils.generate_code_for(
   "amat_neuron.nestml",
   target_path=amat_path,
   module_name="nestml_amat_module",
   logging_level="DEBUG",
   codegen_opts={
    "enable_cse": False
   }
)
print("AMAT NESTML .cpp script produced!")

NESTCodeGeneratorUtils.generate_code_for(
   "amat_neuron.nestml",
   target_path=amat_cse_path,
   module_name="nestml_amat_cse_module",
   logging_level="DEBUG",
   codegen_opts={
    "enable_cse": True
   }
)

print("AMAT NESTML CSE optimisation .cpp script produced!")
