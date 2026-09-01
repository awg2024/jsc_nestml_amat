import nest
import numpy as np


# ------------------------------------------------------------------
# Settings
# ------------------------------------------------------------------

DT = 0.01
SIMTIME = 200.0

NATIVE_MODEL = "amat2_psc_exp"
NESTML_MODEL = "amat_neuron_nestml"
NESTML_MODULE = "nestml_amat_cse_module"

BETA = 4.0

# Keep threshold extremely high so neither neuron can spike.
OMEGA = 1000.0

# Constant current is deliberate:
# no network, no spike timing, no current generator.
#
# This isolates the V_m -> V_th_v analytical dynamics.
I_E = 200.0


# ------------------------------------------------------------------
# Helpers
# ------------------------------------------------------------------

def set_if_available(node, values):
    """
    Set only parameters that exist on this particular model.
    Useful because native NEST and NESTML use slightly different
    parameter names for things such as tau_syn_ex/tau_syn_exc.
    """
    defaults = nest.GetDefaults(node.model)

    accepted = {
        key: value
        for key, value in values.items()
        if key in defaults
    }

    node.set(accepted)


def extract_events(multimeter):
    events = multimeter.events

    return {
        key: np.asarray(value)
        for key, value in events.items()
    }


def compare(name, native, nestml):
    n = min(len(native), len(nestml))

    a = native[:n]
    b = nestml[:n]

    diff = b - a

    print(f"\n{name}")
    print("-" * 50)
    print(f"N samples : {n}")
    print(f"MAE       : {np.mean(np.abs(diff)):.12g}")
    print(f"RMSE      : {np.sqrt(np.mean(diff**2)):.12g}")
    print(f"max |Δ|   : {np.max(np.abs(diff)):.12g}")

    idx = np.argmax(np.abs(diff))

    print(f"worst idx : {idx}")
    print(f"native    : {a[idx]:.12g}")
    print(f"NESTML    : {b[idx]:.12g}")
    print(f"delta     : {diff[idx]:.12g}")


# ------------------------------------------------------------------
# Fresh NEST process
# ------------------------------------------------------------------

nest.ResetKernel()
nest.resolution = DT

print("NEST version:", nest.__version__)
print("Resolution:", nest.resolution)


# ------------------------------------------------------------------
# Load generated model
# ------------------------------------------------------------------

try:
    nest.Install(NESTML_MODULE)
except nest.kernel.NESTError as exc:
    # If this says module already loaded, that's fine.
    # Any other error should still be visible.
    print("nest.Install:", exc)


if NESTML_MODEL not in nest.node_models:
    raise RuntimeError(
        f"{NESTML_MODEL!r} is not available after installing "
        f"{NESTML_MODULE!r}"
    )


# ------------------------------------------------------------------
# Show exactly what the two models expose
# ------------------------------------------------------------------

native_defaults = nest.GetDefaults(NATIVE_MODEL)
nestml_defaults = nest.GetDefaults(NESTML_MODEL)

print("\nNative recordables:")
print(native_defaults["recordables"])

print("\nNESTML recordables:")
print(nestml_defaults["recordables"])


# ------------------------------------------------------------------
# Create one of each neuron
# ------------------------------------------------------------------

native = nest.Create(NATIVE_MODEL)
nestml = nest.Create(NESTML_MODEL)


# ------------------------------------------------------------------
# Common physical parameters
#
# Native and NESTML parameter naming differs slightly, so we set
# aliases separately where necessary.
# ------------------------------------------------------------------

common = {
    "C_m": 200.0,
    "tau_m": 10.0,
    "E_L": -70.0,
    "I_e": I_E,

    "tau_1": 10.0,
    "tau_2": 200.0,
    "alpha_1": 0.0,
    "alpha_2": 0.0,

    "omega": OMEGA,
    "beta": BETA,
    "tau_v": 5.0,
}

set_if_available(native, common)
set_if_available(nestml, common)


# Native names
set_if_available(
    native,
    {
        "tau_syn_ex": 1.0,
        "tau_syn_in": 3.0,
        "t_ref": 2.0,
    },
)

# NESTML names
set_if_available(
    nestml,
    {
        "tau_syn_exc": 1.0,
        "tau_syn_inh": 3.0,
        "refr_T": 2.0,
    },
)


# ------------------------------------------------------------------
# Explicit initial state
# ------------------------------------------------------------------

set_if_available(
    native,
    {
        "V_m": -70.0,
        "V_th_v": 0.0,
    },
)

set_if_available(
    nestml,
    {
        "V_m": -70.0,
        "V_th_v": 0.0,
        "V_th_v_aux": 0.0,
        "V_th_alpha_1": 0.0,
        "V_th_alpha_2": 0.0,
    },
)


# ------------------------------------------------------------------
# Verify parameters AFTER setting them
# ------------------------------------------------------------------

print("\nNative parameters:")
for key in [
    "C_m", "tau_m", "E_L", "I_e",
    "omega", "beta", "tau_v",
    "tau_syn_ex", "tau_syn_in"
]:
    if key in native_defaults:
        print(f"  {key:15s} = {native.get(key)}")


print("\nNESTML parameters:")
for key in [
    "C_m", "tau_m", "E_L", "I_e",
    "omega", "beta", "tau_v",
    "tau_syn_exc", "tau_syn_inh"
]:
    if key in nestml_defaults:
        print(f"  {key:15s} = {nestml.get(key)}")


# ------------------------------------------------------------------
# Record
# ------------------------------------------------------------------

native_recordables = native_defaults["recordables"]
nestml_recordables = nestml_defaults["recordables"]

required_native = ["V_m", "V_th_v"]
required_nestml = ["V_m", "V_th_v"]

for name in required_native:
    if name not in native_recordables:
        raise RuntimeError(
            f"Native model does not expose {name!r}. "
            f"Available: {native_recordables}"
        )

for name in required_nestml:
    if name not in nestml_recordables:
        raise RuntimeError(
            f"NESTML model does not expose {name!r}. "
            f"Available: {nestml_recordables}"
        )


mm_native = nest.Create(
    "multimeter",
    params={
        "record_from": ["V_m", "V_th_v"],
        "interval": DT,
    },
)

mm_nestml = nest.Create(
    "multimeter",
    params={
        "record_from": ["V_m", "V_th_v", "V_th_v_aux"],
        "interval": DT,
    },
)

nest.Connect(mm_native, native)
nest.Connect(mm_nestml, nestml)


# ------------------------------------------------------------------
# Run
# ------------------------------------------------------------------

print(f"\nSimulating {SIMTIME} ms...")
nest.Simulate(SIMTIME)


# ------------------------------------------------------------------
# Compare
# ------------------------------------------------------------------

native_events = extract_events(mm_native)
nestml_events = extract_events(mm_nestml)

compare(
    "V_m",
    native_events["V_m"],
    nestml_events["V_m"],
)

compare(
    "V_th_v",
    native_events["V_th_v"],
    nestml_events["V_th_v"],
)


# ------------------------------------------------------------------
# A few actual values, so we're not hiding the trajectory behind
# one summary statistic.
# ------------------------------------------------------------------

print("\nFirst 10 V_th_v samples")
print("       native              NESTML              delta")

n = min(
    10,
    len(native_events["V_th_v"]),
    len(nestml_events["V_th_v"]),
)

for i in range(n):
    a = native_events["V_th_v"][i]
    b = nestml_events["V_th_v"][i]

    print(
        f"{i:3d}  "
        f"{a:18.12e}  "
        f"{b:18.12e}  "
        f"{b-a:18.12e}"
    )


print("\nFinal values")
print("Native V_m       :", native_events["V_m"][-1])
print("NESTML V_m       :", nestml_events["V_m"][-1])

print("Native V_th_v    :", native_events["V_th_v"][-1])
print("NESTML V_th_v    :", nestml_events["V_th_v"][-1])

print(
    "Final V_th_v Δ  :",
    nestml_events["V_th_v"][-1]
    - native_events["V_th_v"][-1],
)

