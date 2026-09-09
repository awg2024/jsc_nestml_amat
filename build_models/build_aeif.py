import os 
from pynestml.codegeneration.nest_code_generator_utils import NESTCodeGeneratorUtils

base_dir = "/p/project1/paj2623/gray2/benchmark/Running"

# build specific paths and mkdir 
hh_path = os.path.join(base_dir, "targets_aeif/target")
hh_cse_path = os.path.join(base_dir, "targets_aeif_optimised_cse/target")

os.makedirs(hh_path, exist_ok=True)
os.makedirs(hh_cse_path, exist_ok=True)

#nestml amat generation  
NESTCodeGeneratorUtils.generate_code_for(
   "aeif_psc_alpha_neuron.nestml",
   target_path=hh_path,
   module_name="nestml_aeif_module",
   logging_level="DEBUG",
   codegen_opts={
    "enable_cse": False,
   }
)
print("AEIF NESTML .cpp script produced!")

NESTCodeGeneratorUtils.generate_code_for(
   "aeif_psc_alpha_neuron.nestml",
   target_path=hh_cse_path,
   module_name="nestml_aeif_cse_module",
   logging_level="DEBUG",
   codegen_opts={
    "enable_cse": True,
    "preserve_expressions": False,
   }
)

print("AEIF NESTML CSE optimisation .cpp script produced!")


