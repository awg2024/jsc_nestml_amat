import os 
from pynestml.codegeneration.nest_code_generator_utils import NESTCodeGeneratorUtils

base_dir = "/p/project1/paj2623/gray2/benchmark/Running"

# build specific paths and mkdir 
hh_path = os.path.join(base_dir, "targets_hh/target")
hh_cse_path = os.path.join(base_dir, "targets_hh_optimised_cse/target")

os.makedirs(hh_path, exist_ok=True)
os.makedirs(hh_cse_path, exist_ok=True)

# nestml amat generation  
NESTCodeGeneratorUtils.generate_code_for(
   "hh_psc_alpha_custom.nestml",
   target_path=hh_path,
   module_name="nestml_hh_module",
   logging_level="DEBUG",
   codegen_opts={
    "enable_cse": False
   }
)
print("HH NESTML .cpp script produced!")

NESTCodeGeneratorUtils.generate_code_for(
   "hh_psc_alpha_custom.nestml",
   target_path=hh_cse_path,
   module_name="nestml_hh_cse_module",
   logging_level="DEBUG",
   codegen_opts={
    "enable_cse": True
   }
)

print("HH NESTML CSE optimisation .cpp script produced!")


