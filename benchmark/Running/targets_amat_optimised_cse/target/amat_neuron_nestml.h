
/**
 *  amat_neuron_nestml.h
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Generated from NESTML 8.3.0-rc3-post-dev at time: 2026-08-27 15:52:03.758081
**/
#ifndef AMAT_NEURON_NESTML
#define AMAT_NEURON_NESTML

#ifndef HAVE_LIBLTDL
#error "NEST was compiled without support for dynamic loading. Please install libltdl and recompile NEST."
#endif

// C++ includes:
#include <cmath>

#include "config.h"

// Includes from nestkernel:
#include "structural_plasticity_node.h"
#include "connection.h"
#include "dict_util.h"
#include "event.h"
#include "nest_types.h"
#include "ring_buffer.h"
#include "universal_data_logger.h"
// Includes from sli:
#include "dictdatum.h"

// uncomment the next line to enable printing of detailed debug information
// #define DEBUG

namespace nest
{
namespace amat_neuron_nestml_names
{
    // state variables
    const Name _V_th_alpha_1( "V_th_alpha_1" );
    const Name _V_th_alpha_2( "V_th_alpha_2" );
    const Name _V_th_v( "V_th_v" );
    const Name _V_th_v_aux( "V_th_v_aux" );
    const Name _V_m( "V_m" );
    const Name _refr_t( "refr_t" );
    const Name _I_kernel_inh__X__inh_spikes( "I_kernel_inh__X__inh_spikes" );
    const Name _I_kernel_exc__X__exc_spikes( "I_kernel_exc__X__exc_spikes" );
    // inline expressions
    const Name _I_syn_ex( "I_syn_ex" );
    const Name _I_syn_in( "I_syn_in" );
    const Name _I_syn( "I_syn" );
    const Name _V_th( "V_th" );
    // parameters
    const Name _tau_m( "tau_m" );
    const Name _C_m( "C_m" );
    const Name _refr_T( "refr_T" );
    const Name _E_L( "E_L" );
    const Name _tau_syn_exc( "tau_syn_exc" );
    const Name _tau_syn_inh( "tau_syn_inh" );
    const Name _tau_1( "tau_1" );
    const Name _tau_2( "tau_2" );
    const Name _alpha_1( "alpha_1" );
    const Name _alpha_2( "alpha_2" );
    const Name _omega( "omega" );
    const Name _tau_v( "tau_v" );
    const Name _beta( "beta" );
    const Name _I_e( "I_e" );
    // internals
    const Name _unit_psc( "unit_psc" );
    const Name ___h( "__h" );
    const Name ___ode_cse_prop_0( "__ode_cse_prop_0" );
    const Name ___ode_cse_prop_1( "__ode_cse_prop_1" );
    const Name ___ode_cse_prop_2( "__ode_cse_prop_2" );
    const Name ___ode_cse_prop_3( "__ode_cse_prop_3" );
    const Name ___ode_cse_prop_4( "__ode_cse_prop_4" );
    const Name ___ode_cse_prop_5( "__ode_cse_prop_5" );
    const Name ___ode_cse_prop_6( "__ode_cse_prop_6" );
    const Name ___ode_cse_prop_7( "__ode_cse_prop_7" );
    const Name ___ode_cse_prop_8( "__ode_cse_prop_8" );
    const Name ___ode_cse_prop_9( "__ode_cse_prop_9" );
    const Name ___ode_cse_prop_10( "__ode_cse_prop_10" );
    const Name ___ode_cse_prop_11( "__ode_cse_prop_11" );
    const Name ___ode_cse_prop_12( "__ode_cse_prop_12" );
    const Name ___ode_cse_prop_13( "__ode_cse_prop_13" );
    const Name ___ode_cse_prop_14( "__ode_cse_prop_14" );
    const Name ___ode_cse_prop_15( "__ode_cse_prop_15" );
    const Name ___ode_cse_prop_16( "__ode_cse_prop_16" );
    const Name ___ode_cse_prop_17( "__ode_cse_prop_17" );
    const Name ___ode_cse_prop_18( "__ode_cse_prop_18" );
    const Name ___ode_cse_prop_19( "__ode_cse_prop_19" );
    const Name ___ode_cse_prop_20( "__ode_cse_prop_20" );
    const Name ___ode_cse_prop_21( "__ode_cse_prop_21" );
    const Name ___ode_cse_prop_22( "__ode_cse_prop_22" );
    const Name ___ode_cse_prop_23( "__ode_cse_prop_23" );
    const Name ___ode_cse_prop_24( "__ode_cse_prop_24" );
    const Name ___ode_cse_prop_25( "__ode_cse_prop_25" );
    const Name ___ode_cse_prop_26( "__ode_cse_prop_26" );
    const Name ___ode_cse_prop_27( "__ode_cse_prop_27" );
    const Name ___ode_cse_prop_28( "__ode_cse_prop_28" );
    const Name ___ode_cse_prop_29( "__ode_cse_prop_29" );
    const Name ___ode_cse_prop_30( "__ode_cse_prop_30" );
    const Name ___ode_cse_prop_31( "__ode_cse_prop_31" );
    const Name ___ode_cse_prop_32( "__ode_cse_prop_32" );
    const Name ___ode_cse_prop_33( "__ode_cse_prop_33" );
    const Name ___ode_cse_prop_34( "__ode_cse_prop_34" );
    const Name ___ode_cse_prop_35( "__ode_cse_prop_35" );
    const Name ___ode_cse_prop_36( "__ode_cse_prop_36" );
    const Name ___ode_cse_prop_37( "__ode_cse_prop_37" );
    const Name ___ode_cse_prop_38( "__ode_cse_prop_38" );
    const Name ___ode_cse_prop_39( "__ode_cse_prop_39" );
    const Name ___ode_cse_prop_40( "__ode_cse_prop_40" );
    const Name ___ode_cse_prop_41( "__ode_cse_prop_41" );
    const Name ___ode_cse_prop_42( "__ode_cse_prop_42" );
    const Name ___ode_cse_prop_43( "__ode_cse_prop_43" );
    const Name ___ode_cse_prop_44( "__ode_cse_prop_44" );
    const Name ___ode_cse_prop_45( "__ode_cse_prop_45" );
    const Name ___ode_cse_prop_46( "__ode_cse_prop_46" );
    const Name ___ode_cse_prop_47( "__ode_cse_prop_47" );
    const Name ___ode_cse_prop_48( "__ode_cse_prop_48" );
    const Name ___ode_cse_prop_49( "__ode_cse_prop_49" );
    const Name ___ode_cse_prop_50( "__ode_cse_prop_50" );
    const Name ___ode_cse_prop_51( "__ode_cse_prop_51" );
    const Name ___ode_cse_prop_52( "__ode_cse_prop_52" );
    const Name ___ode_cse_prop_53( "__ode_cse_prop_53" );
    const Name ___ode_cse_prop_54( "__ode_cse_prop_54" );
    const Name ___ode_cse_prop_55( "__ode_cse_prop_55" );
    const Name ___ode_cse_prop_56( "__ode_cse_prop_56" );
    const Name ___ode_cse_prop_57( "__ode_cse_prop_57" );
    const Name ___ode_cse_prop_58( "__ode_cse_prop_58" );
    const Name ___ode_cse_prop_59( "__ode_cse_prop_59" );
    const Name ___ode_cse_prop_60( "__ode_cse_prop_60" );
    const Name ___ode_cse_prop_61( "__ode_cse_prop_61" );
    const Name ___ode_cse_prop_62( "__ode_cse_prop_62" );
    const Name ___ode_cse_prop_63( "__ode_cse_prop_63" );
    const Name ___ode_cse_prop_64( "__ode_cse_prop_64" );
    const Name ___ode_cse_prop_65( "__ode_cse_prop_65" );
    const Name ___ode_cse_prop_66( "__ode_cse_prop_66" );
    const Name ___ode_cse_prop_67( "__ode_cse_prop_67" );
    const Name ___ode_cse_prop_68( "__ode_cse_prop_68" );
    const Name ___ode_cse_prop_69( "__ode_cse_prop_69" );
    const Name ___ode_cse_prop_70( "__ode_cse_prop_70" );
    const Name ___ode_cse_prop_71( "__ode_cse_prop_71" );
    const Name ___ode_cse_prop_72( "__ode_cse_prop_72" );
    const Name ___ode_cse_prop_73( "__ode_cse_prop_73" );
    const Name ___ode_cse_prop_74( "__ode_cse_prop_74" );
    const Name ___ode_cse_prop_75( "__ode_cse_prop_75" );
    const Name ___ode_cse_prop_76( "__ode_cse_prop_76" );
    const Name ___ode_cse_prop_77( "__ode_cse_prop_77" );
    const Name ___P__V_th_alpha_1__V_th_alpha_1( "__P__V_th_alpha_1__V_th_alpha_1" );
    const Name ___P__V_th_alpha_2__V_th_alpha_2( "__P__V_th_alpha_2__V_th_alpha_2" );
    const Name ___P__V_m__V_m( "__P__V_m__V_m" );
    const Name ___P__V_m__I_kernel_inh__X__inh_spikes( "__P__V_m__I_kernel_inh__X__inh_spikes" );
    const Name ___P__V_m__I_kernel_exc__X__exc_spikes( "__P__V_m__I_kernel_exc__X__exc_spikes" );
    const Name ___P__V_th_v_aux__V_m( "__P__V_th_v_aux__V_m" );
    const Name ___P__V_th_v_aux__V_th_v_aux( "__P__V_th_v_aux__V_th_v_aux" );
    const Name ___P__V_th_v_aux__I_kernel_inh__X__inh_spikes( "__P__V_th_v_aux__I_kernel_inh__X__inh_spikes" );
    const Name ___P__V_th_v_aux__I_kernel_exc__X__exc_spikes( "__P__V_th_v_aux__I_kernel_exc__X__exc_spikes" );
    const Name ___P__V_th_v__V_m( "__P__V_th_v__V_m" );
    const Name ___P__V_th_v__V_th_v_aux( "__P__V_th_v__V_th_v_aux" );
    const Name ___P__V_th_v__V_th_v( "__P__V_th_v__V_th_v" );
    const Name ___P__V_th_v__I_kernel_inh__X__inh_spikes( "__P__V_th_v__I_kernel_inh__X__inh_spikes" );
    const Name ___P__V_th_v__I_kernel_exc__X__exc_spikes( "__P__V_th_v__I_kernel_exc__X__exc_spikes" );
    const Name ___P__refr_t__refr_t( "__P__refr_t__refr_t" );
    const Name ___P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes( "__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes" );
    const Name ___P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes( "__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes" );

    const Name gsl_abs_error_tol("gsl_abs_error_tol");
    const Name gsl_rel_error_tol("gsl_rel_error_tol");
}
}




#include "nest_time.h"

typedef size_t nest_port_t;
typedef size_t nest_rport_t;

/* BeginDocumentation
  Name: amat_neuron_nestml

  Description:

    amat_neuron - Non-resetting leaky integrate-and-fire neuron with exponential PSCs and a multi-timescale adaptive threshold augmented with a voltage-dependency term (AMAT model)
  ################################################################################################################################################################################

  Description
  +++++++++++

  amat_neuron NESTML script extends mat2_psc_exp by adding a voltage-dependent term to the
  adaptive threshold, as proposed by Yamauchi, Kim & Shinomoto (2011). The
  threshold is now the sum of THREE components on top of the resting value omega:

    1. V_th_alpha_1, V_th_alpha_2 : the original two-timescale spike-history
       terms, unchanged from mat2_psc_exp. Each own spike adds alpha_1/alpha_2
       and the terms decay with time constants tau_1/tau_2.

    2. V_th_v : a new term driven continuously by dV/dt (NOT by spikes). It is
       the convolution of dV/dt with an alpha-function kernel K(s) = s*exp(-s/tau_V),
       scaled by beta. This convolution is implemented exactly as a pair of
       coupled linear ODEs (V_th_v, V_th_v_aux), derived via the Laplace-transform
       / alpha-kernel decomposition described in Yamauchi et al. (2011)

  Variable Description
  +++++++++++
  State variables (evolve over time during simulation):
    V_m          [mV]     Membrane potential, absolute (not relative to E_L).
                           Not reset on spike -- only the threshold moves.
    V_th_alpha_1 [mV]     Short-timescale component of the spike-history
                           threshold, theta_1(t) in the paper.
    V_th_alpha_2 [mV]     Long-timescale component of the spike-history
                           threshold, theta_2(t) in the paper.
    V_th_v       [mV]     Voltage-dependent threshold component, theta_V(t)
                           in the paper. Driven continuously by dV/dt, never
                           jumps at a spike.
    V_th_v_aux   [mV/ms]  Auxiliary variable w = dV_th_v/dt + V_th_v/tau_V.
                           Needed because the alpha-kernel convolution
                           defining V_th_v is mathematically a *second*-order
                           ODE; introducing w splits it into two coupled
                           *first*-order ODEs, which is what the simulator
                           can actually integrate.
    refr_t       [ms]     Countdown timer for the absolute refractory period.
                           Counts down from refr_T to 0 after each spike.

  Parameters (fixed for the duration of a simulation, defined by the user/defaults):
    tau_m       [ms]    Membrane time constant.
    C_m         [pF]    Membrane capacitance.
    refr_T      [ms]    Duration of the absolute refractory period.
    E_L         [mV]    Resting potential.
    tau_syn_exc [ms]    Time constant of excitatory postsynaptic currents.
    tau_syn_inh [ms]    Time constant of inhibitory postsynaptic currents.
    tau_1       [ms]    Decay time constant of V_th_alpha_1.
    tau_2       [ms]    Decay time constant of V_th_alpha_2.
    alpha_1     [mV]    Amount V_th_alpha_1 jumps by on each own spike.
    alpha_2     [mV]    Amount V_th_alpha_2 jumps by on each own spike.
    omega       [mV]    Resting spike threshold (absolute, not relative to E_L).
    tau_V       [ms]    Timescale of the voltage-dependency kernel
                         K(s) = s*exp(-s/tau_V). Fixed at 5 ms in the paper.
    beta        [1/ms]  Strength and sign of the voltage dependency.
                         beta = 0  -> V_th_v stays at 0, model is identical
                                      to the original mat2_psc_exp.
                         beta < 0  -> phasic / rebound-type behaviour.
                         beta > 0  -> resonator / subthreshold-oscillation
                                      type behaviour.
    I_e         [pA]    Constant external input current.

  Internals (derived once, from the parameters above and the simulation
  resolution; not set directly by the user):
    h        [ms]   Simulation time step (the simulation resolution).
    P11th    [real] Per-step decay factor for V_th_alpha_1: exp(-h/tau_1).
    P22th    [real] Per-step decay factor for V_th_alpha_2: exp(-h/tau_2).
    unit_psc [pA]   Unit-conversion constant for postsynaptic current amplitude.

  Input:
    exc_spikes         Excitatory spike train received by the neuron.
    inh_spikes         Inhibitory spike train received by the neuron.
    I_stim      [pA]   Externally injected continuous current (e.g. a current
                        generator device connected to this neuron).

  Output:
    spike              Emitted whenever the threshold condition is satisfied.

  References
  ++++++++++

  .. [1] Rotter S and Diesmann M (1999). Exact simulation of
         time-invariant linear systems with applications to neuronal
         modeling. Biological Cybernetics 81:381-402.
         DOI: https://doi.org/10.1007/s004220050570

  .. [2] Diesmann M, Gewaltig M-O, Rotter S, Aertsen A (2001). State
         space analysis of synchronous spiking in cortical neural
         networks. Neurocomputing 38-40:565-571.
         DOI:https://doi.org/10.1016/S0925-2312(01)00409-X

  .. [3] Kobayashi R, Tsubo Y and Shinomoto S (2009). Made-to-order
         spiking neuron model equipped with a multi-timescale adaptive
         threshold. Frontiers in Computational Neuroscience 3:9.
         DOI: https://doi.org/10.3389/neuro.10.009.2009

  .. [4] Yamauchi S, Kim H and Shinomoto S (2011). Elemental spiking
         neuron model for reproducing diverse firing patterns and
         predicting precise firing times. Frontiers in Computational
         Neuroscience 5:42. DOI: https://doi.org/10.3389/fncom.2011.00042

  Copyright statement
  +++++++++++++++++++

  This file is part of NEST.

  Copyright (C) 2004 The NEST Initiative

  NEST is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  NEST is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with NEST.  If not, see <http://www.gnu.org/licenses/>.



  Parameters:
  The following parameters can be set in the status dictionary.
tau_m [ms] membrane parameters (unchanged from mat2_psc_exp) 
 Membrane time constant (Yamauchi et al. explicitly states to use 10 ms)
C_m [pF]  Capacitance of the membrane
refr_T [ms]  Duration of refractory period
E_L [mV]  Resting potential
tau_syn_exc [ms]  Time constant of postsynaptic excitatory currents
tau_syn_inh [ms]  Time constant of postsynaptic inhibitory currents
tau_1 [ms] spike-history threshold parameters (unchanged from mat2_psc_exp) 
 Short time constant of adaptive threshold
tau_2 [ms]  Long time constant of adaptive threshold
alpha_1 [mV]  Amplitude of short time threshold adaptation [3]
alpha_2 [mV]  Amplitude of long time threshold adaptation [4]
omega [mV]  This value is relative to E_L (resting spike offset) 
tau_v [ms] voltage-dependent threshold parameters (new, AMAT extension) 
 Timescale of the voltage-dependency kernel K(s)=s*exp(-s/tau_v) [4]
beta [1 / ms]  Strength/sign of voltage dependency. beta=0 recovers mat2_psc_exp
I_e [pA]  constant external input current


  Dynamic state variables:
V_th_alpha_1 [mV] spike-history threshold (oringal MAT neuronal model)
 theta_1(t): short-timescale spike-history threshold
V_th_alpha_2 [mV]  theta_2(t): long-timescale spike-history threshold
V_th_v [mV] voltage-dependent threshold (AMAT extension)
 theta_V(t): voltage-dependent threshold term
V_th_v_aux [mV / ms]  Auxiliary variable w = dtheta_V/dt + theta_V/tau_V,
V_m [mV] needed to express the alpha-kernel convolution as two
coupled first-order ODEs instead of one 2nd-order ODE. 
membrane potential and refractory timer 
 Absolute membrane potential; never reset on spike
refr_t [ms]  Refractory period timer; counts down to 0 after a spike


  Sends: nest::SpikeEvent

  Receives: Spike, Current, DataLoggingRequest
*/

// Register the neuron model
void register_amat_neuron_nestml( const std::string& name );

class amat_neuron_nestml : public nest::StructuralPlasticityNode
{
public:
  /**
   * The constructor is only used to create the model prototype in the model manager.
  **/
  amat_neuron_nestml();

  /**
   * The copy constructor is used to create model copies and instances of the model.
   * @node The copy constructor needs to initialize the parameters and the state.
   *       Initialization of buffers and interal variables is deferred to
   *       @c init_buffers_() and @c pre_run_hook() (or calibrate() in NEST 3.3 and older).
  **/
  amat_neuron_nestml(const amat_neuron_nestml &);

  /**
   * Destructor.
  **/
  ~amat_neuron_nestml() override;

  // -------------------------------------------------------------------------
  //   Import sets of overloaded virtual functions.
  //   See: Technical Issues / Virtual Functions: Overriding, Overloading,
  //        and Hiding
  // -------------------------------------------------------------------------

  using nest::Node::handles_test_event;
  using nest::Node::handle;

  /**
   * Used to validate that we can send nest::SpikeEvent to desired target:port.
  **/
  nest_port_t send_test_event(nest::Node& target, nest_rport_t receptor_type, nest::synindex, bool) override;


  // -------------------------------------------------------------------------
  //   Functions handling incoming events.
  //   We tell nest that we can handle incoming events of various types by
  //   defining handle() for the given event.
  // -------------------------------------------------------------------------


  void handle(nest::SpikeEvent &) override;        //! accept spikes
  void handle(nest::CurrentEvent &) override;      //! accept input current

  void handle(nest::DataLoggingRequest &) override;//! allow recording with multimeter
  nest_port_t handles_test_event(nest::SpikeEvent&, nest_port_t) override;
  nest_port_t handles_test_event(nest::CurrentEvent&, nest_port_t) override;
  nest_port_t handles_test_event(nest::DataLoggingRequest&, nest_port_t) override;

  // -------------------------------------------------------------------------
  //   Functions for getting/setting parameters and state values.
  // -------------------------------------------------------------------------

  void get_status(DictionaryDatum&) const override;
  void set_status(const DictionaryDatum&) override;


  // -------------------------------------------------------------------------
  //   Getters/setters for state block
  // -------------------------------------------------------------------------

  inline double get_V_th_alpha_1() const
  {
    return S_.V_th_alpha_1;
  }inline void set_V_th_alpha_1(const double __v)
  {
    S_.V_th_alpha_1 = __v;
  }

  inline double get_V_th_alpha_2() const
  {
    return S_.V_th_alpha_2;
  }inline void set_V_th_alpha_2(const double __v)
  {
    S_.V_th_alpha_2 = __v;
  }

  inline double get_V_th_v() const
  {
    return S_.V_th_v;
  }inline void set_V_th_v(const double __v)
  {
    S_.V_th_v = __v;
  }

  inline double get_V_th_v_aux() const
  {
    return S_.V_th_v_aux;
  }inline void set_V_th_v_aux(const double __v)
  {
    S_.V_th_v_aux = __v;
  }

  inline double get_V_m() const
  {
    return S_.V_m;
  }inline void set_V_m(const double __v)
  {
    S_.V_m = __v;
  }

  inline double get_refr_t() const
  {
    return S_.refr_t;
  }inline void set_refr_t(const double __v)
  {
    S_.refr_t = __v;
  }

  inline double get_I_kernel_inh__X__inh_spikes() const
  {
    return S_.I_kernel_inh__X__inh_spikes;
  }inline void set_I_kernel_inh__X__inh_spikes(const double __v)
  {
    S_.I_kernel_inh__X__inh_spikes = __v;
  }

  inline double get_I_kernel_exc__X__exc_spikes() const
  {
    return S_.I_kernel_exc__X__exc_spikes;
  }inline void set_I_kernel_exc__X__exc_spikes(const double __v)
  {
    S_.I_kernel_exc__X__exc_spikes = __v;
  }


  // -------------------------------------------------------------------------
  //   Getters/setters for parameters
  // -------------------------------------------------------------------------

  inline double get_tau_m() const
  {
    return P_.tau_m;
  }inline void set_tau_m(const double __v)
  {
    P_.tau_m = __v;
  }

  inline double get_C_m() const
  {
    return P_.C_m;
  }inline void set_C_m(const double __v)
  {
    P_.C_m = __v;
  }

  inline double get_refr_T() const
  {
    return P_.refr_T;
  }inline void set_refr_T(const double __v)
  {
    P_.refr_T = __v;
  }

  inline double get_E_L() const
  {
    return P_.E_L;
  }inline void set_E_L(const double __v)
  {
    P_.E_L = __v;
  }

  inline double get_tau_syn_exc() const
  {
    return P_.tau_syn_exc;
  }inline void set_tau_syn_exc(const double __v)
  {
    P_.tau_syn_exc = __v;
  }

  inline double get_tau_syn_inh() const
  {
    return P_.tau_syn_inh;
  }inline void set_tau_syn_inh(const double __v)
  {
    P_.tau_syn_inh = __v;
  }

  inline double get_tau_1() const
  {
    return P_.tau_1;
  }inline void set_tau_1(const double __v)
  {
    P_.tau_1 = __v;
  }

  inline double get_tau_2() const
  {
    return P_.tau_2;
  }inline void set_tau_2(const double __v)
  {
    P_.tau_2 = __v;
  }

  inline double get_alpha_1() const
  {
    return P_.alpha_1;
  }inline void set_alpha_1(const double __v)
  {
    P_.alpha_1 = __v;
  }

  inline double get_alpha_2() const
  {
    return P_.alpha_2;
  }inline void set_alpha_2(const double __v)
  {
    P_.alpha_2 = __v;
  }

  inline double get_omega() const
  {
    return P_.omega;
  }inline void set_omega(const double __v)
  {
    P_.omega = __v;
  }

  inline double get_tau_v() const
  {
    return P_.tau_v;
  }inline void set_tau_v(const double __v)
  {
    P_.tau_v = __v;
  }

  inline double get_beta() const
  {
    return P_.beta;
  }inline void set_beta(const double __v)
  {
    P_.beta = __v;
  }

  inline double get_I_e() const
  {
    return P_.I_e;
  }inline void set_I_e(const double __v)
  {
    P_.I_e = __v;
  }


  // -------------------------------------------------------------------------
  //   Getters/setters for internals
  // -------------------------------------------------------------------------

  inline double get_unit_psc() const
  {
    return V_.unit_psc;
  }inline void set_unit_psc(const double __v)
  {
    V_.unit_psc = __v;
  }
  inline double get___h() const
  {
    return V_.__h;
  }inline void set___h(const double __v)
  {
    V_.__h = __v;
  }
  inline double get___ode_cse_prop_0() const
  {
    return V_.__ode_cse_prop_0;
  }inline void set___ode_cse_prop_0(const double __v)
  {
    V_.__ode_cse_prop_0 = __v;
  }
  inline double get___ode_cse_prop_1() const
  {
    return V_.__ode_cse_prop_1;
  }inline void set___ode_cse_prop_1(const double __v)
  {
    V_.__ode_cse_prop_1 = __v;
  }
  inline double get___ode_cse_prop_2() const
  {
    return V_.__ode_cse_prop_2;
  }inline void set___ode_cse_prop_2(const double __v)
  {
    V_.__ode_cse_prop_2 = __v;
  }
  inline double get___ode_cse_prop_3() const
  {
    return V_.__ode_cse_prop_3;
  }inline void set___ode_cse_prop_3(const double __v)
  {
    V_.__ode_cse_prop_3 = __v;
  }
  inline double get___ode_cse_prop_4() const
  {
    return V_.__ode_cse_prop_4;
  }inline void set___ode_cse_prop_4(const double __v)
  {
    V_.__ode_cse_prop_4 = __v;
  }
  inline double get___ode_cse_prop_5() const
  {
    return V_.__ode_cse_prop_5;
  }inline void set___ode_cse_prop_5(const double __v)
  {
    V_.__ode_cse_prop_5 = __v;
  }
  inline double get___ode_cse_prop_6() const
  {
    return V_.__ode_cse_prop_6;
  }inline void set___ode_cse_prop_6(const double __v)
  {
    V_.__ode_cse_prop_6 = __v;
  }
  inline double get___ode_cse_prop_7() const
  {
    return V_.__ode_cse_prop_7;
  }inline void set___ode_cse_prop_7(const double __v)
  {
    V_.__ode_cse_prop_7 = __v;
  }
  inline double get___ode_cse_prop_8() const
  {
    return V_.__ode_cse_prop_8;
  }inline void set___ode_cse_prop_8(const double __v)
  {
    V_.__ode_cse_prop_8 = __v;
  }
  inline double get___ode_cse_prop_9() const
  {
    return V_.__ode_cse_prop_9;
  }inline void set___ode_cse_prop_9(const double __v)
  {
    V_.__ode_cse_prop_9 = __v;
  }
  inline double get___ode_cse_prop_10() const
  {
    return V_.__ode_cse_prop_10;
  }inline void set___ode_cse_prop_10(const double __v)
  {
    V_.__ode_cse_prop_10 = __v;
  }
  inline double get___ode_cse_prop_11() const
  {
    return V_.__ode_cse_prop_11;
  }inline void set___ode_cse_prop_11(const double __v)
  {
    V_.__ode_cse_prop_11 = __v;
  }
  inline double get___ode_cse_prop_12() const
  {
    return V_.__ode_cse_prop_12;
  }inline void set___ode_cse_prop_12(const double __v)
  {
    V_.__ode_cse_prop_12 = __v;
  }
  inline double get___ode_cse_prop_13() const
  {
    return V_.__ode_cse_prop_13;
  }inline void set___ode_cse_prop_13(const double __v)
  {
    V_.__ode_cse_prop_13 = __v;
  }
  inline double get___ode_cse_prop_14() const
  {
    return V_.__ode_cse_prop_14;
  }inline void set___ode_cse_prop_14(const double __v)
  {
    V_.__ode_cse_prop_14 = __v;
  }
  inline double get___ode_cse_prop_15() const
  {
    return V_.__ode_cse_prop_15;
  }inline void set___ode_cse_prop_15(const double __v)
  {
    V_.__ode_cse_prop_15 = __v;
  }
  inline double get___ode_cse_prop_16() const
  {
    return V_.__ode_cse_prop_16;
  }inline void set___ode_cse_prop_16(const double __v)
  {
    V_.__ode_cse_prop_16 = __v;
  }
  inline double get___ode_cse_prop_17() const
  {
    return V_.__ode_cse_prop_17;
  }inline void set___ode_cse_prop_17(const double __v)
  {
    V_.__ode_cse_prop_17 = __v;
  }
  inline double get___ode_cse_prop_18() const
  {
    return V_.__ode_cse_prop_18;
  }inline void set___ode_cse_prop_18(const double __v)
  {
    V_.__ode_cse_prop_18 = __v;
  }
  inline double get___ode_cse_prop_19() const
  {
    return V_.__ode_cse_prop_19;
  }inline void set___ode_cse_prop_19(const double __v)
  {
    V_.__ode_cse_prop_19 = __v;
  }
  inline double get___ode_cse_prop_20() const
  {
    return V_.__ode_cse_prop_20;
  }inline void set___ode_cse_prop_20(const double __v)
  {
    V_.__ode_cse_prop_20 = __v;
  }
  inline double get___ode_cse_prop_21() const
  {
    return V_.__ode_cse_prop_21;
  }inline void set___ode_cse_prop_21(const double __v)
  {
    V_.__ode_cse_prop_21 = __v;
  }
  inline double get___ode_cse_prop_22() const
  {
    return V_.__ode_cse_prop_22;
  }inline void set___ode_cse_prop_22(const double __v)
  {
    V_.__ode_cse_prop_22 = __v;
  }
  inline double get___ode_cse_prop_23() const
  {
    return V_.__ode_cse_prop_23;
  }inline void set___ode_cse_prop_23(const double __v)
  {
    V_.__ode_cse_prop_23 = __v;
  }
  inline double get___ode_cse_prop_24() const
  {
    return V_.__ode_cse_prop_24;
  }inline void set___ode_cse_prop_24(const double __v)
  {
    V_.__ode_cse_prop_24 = __v;
  }
  inline double get___ode_cse_prop_25() const
  {
    return V_.__ode_cse_prop_25;
  }inline void set___ode_cse_prop_25(const double __v)
  {
    V_.__ode_cse_prop_25 = __v;
  }
  inline double get___ode_cse_prop_26() const
  {
    return V_.__ode_cse_prop_26;
  }inline void set___ode_cse_prop_26(const double __v)
  {
    V_.__ode_cse_prop_26 = __v;
  }
  inline double get___ode_cse_prop_27() const
  {
    return V_.__ode_cse_prop_27;
  }inline void set___ode_cse_prop_27(const double __v)
  {
    V_.__ode_cse_prop_27 = __v;
  }
  inline double get___ode_cse_prop_28() const
  {
    return V_.__ode_cse_prop_28;
  }inline void set___ode_cse_prop_28(const double __v)
  {
    V_.__ode_cse_prop_28 = __v;
  }
  inline double get___ode_cse_prop_29() const
  {
    return V_.__ode_cse_prop_29;
  }inline void set___ode_cse_prop_29(const double __v)
  {
    V_.__ode_cse_prop_29 = __v;
  }
  inline double get___ode_cse_prop_30() const
  {
    return V_.__ode_cse_prop_30;
  }inline void set___ode_cse_prop_30(const double __v)
  {
    V_.__ode_cse_prop_30 = __v;
  }
  inline double get___ode_cse_prop_31() const
  {
    return V_.__ode_cse_prop_31;
  }inline void set___ode_cse_prop_31(const double __v)
  {
    V_.__ode_cse_prop_31 = __v;
  }
  inline double get___ode_cse_prop_32() const
  {
    return V_.__ode_cse_prop_32;
  }inline void set___ode_cse_prop_32(const double __v)
  {
    V_.__ode_cse_prop_32 = __v;
  }
  inline double get___ode_cse_prop_33() const
  {
    return V_.__ode_cse_prop_33;
  }inline void set___ode_cse_prop_33(const double __v)
  {
    V_.__ode_cse_prop_33 = __v;
  }
  inline double get___ode_cse_prop_34() const
  {
    return V_.__ode_cse_prop_34;
  }inline void set___ode_cse_prop_34(const double __v)
  {
    V_.__ode_cse_prop_34 = __v;
  }
  inline double get___ode_cse_prop_35() const
  {
    return V_.__ode_cse_prop_35;
  }inline void set___ode_cse_prop_35(const double __v)
  {
    V_.__ode_cse_prop_35 = __v;
  }
  inline double get___ode_cse_prop_36() const
  {
    return V_.__ode_cse_prop_36;
  }inline void set___ode_cse_prop_36(const double __v)
  {
    V_.__ode_cse_prop_36 = __v;
  }
  inline double get___ode_cse_prop_37() const
  {
    return V_.__ode_cse_prop_37;
  }inline void set___ode_cse_prop_37(const double __v)
  {
    V_.__ode_cse_prop_37 = __v;
  }
  inline double get___ode_cse_prop_38() const
  {
    return V_.__ode_cse_prop_38;
  }inline void set___ode_cse_prop_38(const double __v)
  {
    V_.__ode_cse_prop_38 = __v;
  }
  inline double get___ode_cse_prop_39() const
  {
    return V_.__ode_cse_prop_39;
  }inline void set___ode_cse_prop_39(const double __v)
  {
    V_.__ode_cse_prop_39 = __v;
  }
  inline double get___ode_cse_prop_40() const
  {
    return V_.__ode_cse_prop_40;
  }inline void set___ode_cse_prop_40(const double __v)
  {
    V_.__ode_cse_prop_40 = __v;
  }
  inline double get___ode_cse_prop_41() const
  {
    return V_.__ode_cse_prop_41;
  }inline void set___ode_cse_prop_41(const double __v)
  {
    V_.__ode_cse_prop_41 = __v;
  }
  inline double get___ode_cse_prop_42() const
  {
    return V_.__ode_cse_prop_42;
  }inline void set___ode_cse_prop_42(const double __v)
  {
    V_.__ode_cse_prop_42 = __v;
  }
  inline double get___ode_cse_prop_43() const
  {
    return V_.__ode_cse_prop_43;
  }inline void set___ode_cse_prop_43(const double __v)
  {
    V_.__ode_cse_prop_43 = __v;
  }
  inline double get___ode_cse_prop_44() const
  {
    return V_.__ode_cse_prop_44;
  }inline void set___ode_cse_prop_44(const double __v)
  {
    V_.__ode_cse_prop_44 = __v;
  }
  inline double get___ode_cse_prop_45() const
  {
    return V_.__ode_cse_prop_45;
  }inline void set___ode_cse_prop_45(const double __v)
  {
    V_.__ode_cse_prop_45 = __v;
  }
  inline double get___ode_cse_prop_46() const
  {
    return V_.__ode_cse_prop_46;
  }inline void set___ode_cse_prop_46(const double __v)
  {
    V_.__ode_cse_prop_46 = __v;
  }
  inline double get___ode_cse_prop_47() const
  {
    return V_.__ode_cse_prop_47;
  }inline void set___ode_cse_prop_47(const double __v)
  {
    V_.__ode_cse_prop_47 = __v;
  }
  inline double get___ode_cse_prop_48() const
  {
    return V_.__ode_cse_prop_48;
  }inline void set___ode_cse_prop_48(const double __v)
  {
    V_.__ode_cse_prop_48 = __v;
  }
  inline double get___ode_cse_prop_49() const
  {
    return V_.__ode_cse_prop_49;
  }inline void set___ode_cse_prop_49(const double __v)
  {
    V_.__ode_cse_prop_49 = __v;
  }
  inline double get___ode_cse_prop_50() const
  {
    return V_.__ode_cse_prop_50;
  }inline void set___ode_cse_prop_50(const double __v)
  {
    V_.__ode_cse_prop_50 = __v;
  }
  inline double get___ode_cse_prop_51() const
  {
    return V_.__ode_cse_prop_51;
  }inline void set___ode_cse_prop_51(const double __v)
  {
    V_.__ode_cse_prop_51 = __v;
  }
  inline double get___ode_cse_prop_52() const
  {
    return V_.__ode_cse_prop_52;
  }inline void set___ode_cse_prop_52(const double __v)
  {
    V_.__ode_cse_prop_52 = __v;
  }
  inline double get___ode_cse_prop_53() const
  {
    return V_.__ode_cse_prop_53;
  }inline void set___ode_cse_prop_53(const double __v)
  {
    V_.__ode_cse_prop_53 = __v;
  }
  inline double get___ode_cse_prop_54() const
  {
    return V_.__ode_cse_prop_54;
  }inline void set___ode_cse_prop_54(const double __v)
  {
    V_.__ode_cse_prop_54 = __v;
  }
  inline double get___ode_cse_prop_55() const
  {
    return V_.__ode_cse_prop_55;
  }inline void set___ode_cse_prop_55(const double __v)
  {
    V_.__ode_cse_prop_55 = __v;
  }
  inline double get___ode_cse_prop_56() const
  {
    return V_.__ode_cse_prop_56;
  }inline void set___ode_cse_prop_56(const double __v)
  {
    V_.__ode_cse_prop_56 = __v;
  }
  inline double get___ode_cse_prop_57() const
  {
    return V_.__ode_cse_prop_57;
  }inline void set___ode_cse_prop_57(const double __v)
  {
    V_.__ode_cse_prop_57 = __v;
  }
  inline double get___ode_cse_prop_58() const
  {
    return V_.__ode_cse_prop_58;
  }inline void set___ode_cse_prop_58(const double __v)
  {
    V_.__ode_cse_prop_58 = __v;
  }
  inline double get___ode_cse_prop_59() const
  {
    return V_.__ode_cse_prop_59;
  }inline void set___ode_cse_prop_59(const double __v)
  {
    V_.__ode_cse_prop_59 = __v;
  }
  inline double get___ode_cse_prop_60() const
  {
    return V_.__ode_cse_prop_60;
  }inline void set___ode_cse_prop_60(const double __v)
  {
    V_.__ode_cse_prop_60 = __v;
  }
  inline double get___ode_cse_prop_61() const
  {
    return V_.__ode_cse_prop_61;
  }inline void set___ode_cse_prop_61(const double __v)
  {
    V_.__ode_cse_prop_61 = __v;
  }
  inline double get___ode_cse_prop_62() const
  {
    return V_.__ode_cse_prop_62;
  }inline void set___ode_cse_prop_62(const double __v)
  {
    V_.__ode_cse_prop_62 = __v;
  }
  inline double get___ode_cse_prop_63() const
  {
    return V_.__ode_cse_prop_63;
  }inline void set___ode_cse_prop_63(const double __v)
  {
    V_.__ode_cse_prop_63 = __v;
  }
  inline double get___ode_cse_prop_64() const
  {
    return V_.__ode_cse_prop_64;
  }inline void set___ode_cse_prop_64(const double __v)
  {
    V_.__ode_cse_prop_64 = __v;
  }
  inline double get___ode_cse_prop_65() const
  {
    return V_.__ode_cse_prop_65;
  }inline void set___ode_cse_prop_65(const double __v)
  {
    V_.__ode_cse_prop_65 = __v;
  }
  inline double get___ode_cse_prop_66() const
  {
    return V_.__ode_cse_prop_66;
  }inline void set___ode_cse_prop_66(const double __v)
  {
    V_.__ode_cse_prop_66 = __v;
  }
  inline double get___ode_cse_prop_67() const
  {
    return V_.__ode_cse_prop_67;
  }inline void set___ode_cse_prop_67(const double __v)
  {
    V_.__ode_cse_prop_67 = __v;
  }
  inline double get___ode_cse_prop_68() const
  {
    return V_.__ode_cse_prop_68;
  }inline void set___ode_cse_prop_68(const double __v)
  {
    V_.__ode_cse_prop_68 = __v;
  }
  inline double get___ode_cse_prop_69() const
  {
    return V_.__ode_cse_prop_69;
  }inline void set___ode_cse_prop_69(const double __v)
  {
    V_.__ode_cse_prop_69 = __v;
  }
  inline double get___ode_cse_prop_70() const
  {
    return V_.__ode_cse_prop_70;
  }inline void set___ode_cse_prop_70(const double __v)
  {
    V_.__ode_cse_prop_70 = __v;
  }
  inline double get___ode_cse_prop_71() const
  {
    return V_.__ode_cse_prop_71;
  }inline void set___ode_cse_prop_71(const double __v)
  {
    V_.__ode_cse_prop_71 = __v;
  }
  inline double get___ode_cse_prop_72() const
  {
    return V_.__ode_cse_prop_72;
  }inline void set___ode_cse_prop_72(const double __v)
  {
    V_.__ode_cse_prop_72 = __v;
  }
  inline double get___ode_cse_prop_73() const
  {
    return V_.__ode_cse_prop_73;
  }inline void set___ode_cse_prop_73(const double __v)
  {
    V_.__ode_cse_prop_73 = __v;
  }
  inline double get___ode_cse_prop_74() const
  {
    return V_.__ode_cse_prop_74;
  }inline void set___ode_cse_prop_74(const double __v)
  {
    V_.__ode_cse_prop_74 = __v;
  }
  inline double get___ode_cse_prop_75() const
  {
    return V_.__ode_cse_prop_75;
  }inline void set___ode_cse_prop_75(const double __v)
  {
    V_.__ode_cse_prop_75 = __v;
  }
  inline double get___ode_cse_prop_76() const
  {
    return V_.__ode_cse_prop_76;
  }inline void set___ode_cse_prop_76(const double __v)
  {
    V_.__ode_cse_prop_76 = __v;
  }
  inline double get___ode_cse_prop_77() const
  {
    return V_.__ode_cse_prop_77;
  }inline void set___ode_cse_prop_77(const double __v)
  {
    V_.__ode_cse_prop_77 = __v;
  }
  inline double get___P__V_th_alpha_1__V_th_alpha_1() const
  {
    return V_.__P__V_th_alpha_1__V_th_alpha_1;
  }inline void set___P__V_th_alpha_1__V_th_alpha_1(const double __v)
  {
    V_.__P__V_th_alpha_1__V_th_alpha_1 = __v;
  }
  inline double get___P__V_th_alpha_2__V_th_alpha_2() const
  {
    return V_.__P__V_th_alpha_2__V_th_alpha_2;
  }inline void set___P__V_th_alpha_2__V_th_alpha_2(const double __v)
  {
    V_.__P__V_th_alpha_2__V_th_alpha_2 = __v;
  }
  inline double get___P__V_m__V_m() const
  {
    return V_.__P__V_m__V_m;
  }inline void set___P__V_m__V_m(const double __v)
  {
    V_.__P__V_m__V_m = __v;
  }
  inline double get___P__V_m__I_kernel_inh__X__inh_spikes() const
  {
    return V_.__P__V_m__I_kernel_inh__X__inh_spikes;
  }inline void set___P__V_m__I_kernel_inh__X__inh_spikes(const double __v)
  {
    V_.__P__V_m__I_kernel_inh__X__inh_spikes = __v;
  }
  inline double get___P__V_m__I_kernel_exc__X__exc_spikes() const
  {
    return V_.__P__V_m__I_kernel_exc__X__exc_spikes;
  }inline void set___P__V_m__I_kernel_exc__X__exc_spikes(const double __v)
  {
    V_.__P__V_m__I_kernel_exc__X__exc_spikes = __v;
  }
  inline double get___P__V_th_v_aux__V_m() const
  {
    return V_.__P__V_th_v_aux__V_m;
  }inline void set___P__V_th_v_aux__V_m(const double __v)
  {
    V_.__P__V_th_v_aux__V_m = __v;
  }
  inline double get___P__V_th_v_aux__V_th_v_aux() const
  {
    return V_.__P__V_th_v_aux__V_th_v_aux;
  }inline void set___P__V_th_v_aux__V_th_v_aux(const double __v)
  {
    V_.__P__V_th_v_aux__V_th_v_aux = __v;
  }
  inline double get___P__V_th_v_aux__I_kernel_inh__X__inh_spikes() const
  {
    return V_.__P__V_th_v_aux__I_kernel_inh__X__inh_spikes;
  }inline void set___P__V_th_v_aux__I_kernel_inh__X__inh_spikes(const double __v)
  {
    V_.__P__V_th_v_aux__I_kernel_inh__X__inh_spikes = __v;
  }
  inline double get___P__V_th_v_aux__I_kernel_exc__X__exc_spikes() const
  {
    return V_.__P__V_th_v_aux__I_kernel_exc__X__exc_spikes;
  }inline void set___P__V_th_v_aux__I_kernel_exc__X__exc_spikes(const double __v)
  {
    V_.__P__V_th_v_aux__I_kernel_exc__X__exc_spikes = __v;
  }
  inline double get___P__V_th_v__V_m() const
  {
    return V_.__P__V_th_v__V_m;
  }inline void set___P__V_th_v__V_m(const double __v)
  {
    V_.__P__V_th_v__V_m = __v;
  }
  inline double get___P__V_th_v__V_th_v_aux() const
  {
    return V_.__P__V_th_v__V_th_v_aux;
  }inline void set___P__V_th_v__V_th_v_aux(const double __v)
  {
    V_.__P__V_th_v__V_th_v_aux = __v;
  }
  inline double get___P__V_th_v__V_th_v() const
  {
    return V_.__P__V_th_v__V_th_v;
  }inline void set___P__V_th_v__V_th_v(const double __v)
  {
    V_.__P__V_th_v__V_th_v = __v;
  }
  inline double get___P__V_th_v__I_kernel_inh__X__inh_spikes() const
  {
    return V_.__P__V_th_v__I_kernel_inh__X__inh_spikes;
  }inline void set___P__V_th_v__I_kernel_inh__X__inh_spikes(const double __v)
  {
    V_.__P__V_th_v__I_kernel_inh__X__inh_spikes = __v;
  }
  inline double get___P__V_th_v__I_kernel_exc__X__exc_spikes() const
  {
    return V_.__P__V_th_v__I_kernel_exc__X__exc_spikes;
  }inline void set___P__V_th_v__I_kernel_exc__X__exc_spikes(const double __v)
  {
    V_.__P__V_th_v__I_kernel_exc__X__exc_spikes = __v;
  }
  inline double get___P__refr_t__refr_t() const
  {
    return V_.__P__refr_t__refr_t;
  }inline void set___P__refr_t__refr_t(const double __v)
  {
    V_.__P__refr_t__refr_t = __v;
  }
  inline double get___P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes() const
  {
    return V_.__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes;
  }inline void set___P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes(const double __v)
  {
    V_.__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes = __v;
  }
  inline double get___P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes() const
  {
    return V_.__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes;
  }inline void set___P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes(const double __v)
  {
    V_.__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes = __v;
  }


  // -------------------------------------------------------------------------
  //   Methods corresponding to event handlers
  // -------------------------------------------------------------------------

  // -------------------------------------------------------------------------
  //   Initialization functions
  // -------------------------------------------------------------------------
  void calibrate_time( const nest::TimeConverter& tc ) override;

protected:

private:
  void recompute_internal_variables(bool exclude_timestep=false);

private:

  static const nest_port_t MIN_SPIKE_RECEPTOR = 0;
  static const nest_port_t PORT_NOT_AVAILABLE = -1;

  enum SynapseTypes
  {
    EXC_SPIKES = 0,
    INH_SPIKES = 1,
    MAX_SPIKE_RECEPTOR = 2
  };

  enum ContinuousInput
  {
    I_STIM = 0,
    NUM_CONTINUOUS_INPUT_PORTS = 1
  };

  static const size_t NUM_SPIKE_RECEPTORS = MAX_SPIKE_RECEPTOR - MIN_SPIKE_RECEPTOR;

static std::vector< std::tuple< int, int > > rport_to_nestml_buffer_idx;

  /**
   * Reset state of neuron.
  **/

  void init_state_internal_();

  /**
   * Reset internal buffers of neuron.
  **/
  void init_buffers_() override;

  /**
   * Initialize auxiliary quantities, leave parameters and state untouched.
  **/
  void pre_run_hook() override;

  /**
   * Take neuron through given time interval
  **/
  void update(nest::Time const &, const long, const long) override;

  // The next two classes need to be friends to access the State_ class/member
  friend class nest::RecordablesMap<amat_neuron_nestml>;
  friend class nest::UniversalDataLogger<amat_neuron_nestml>;

  /**
   * Free parameters of the neuron.
   *


   *
   * These are the parameters that can be set by the user through @c `node.set()`.
   * They are initialized from the model prototype when the node is created.
   * Parameters do not change during calls to @c update() and are not reset by
   * @c ResetNetwork.
   *
   * @note Parameters_ need neither copy constructor nor @c operator=(), since
   *       all its members are copied properly by the default copy constructor
   *       and assignment operator. Important:
   *       - If Parameters_ contained @c Time members, you need to define the
   *         assignment operator to recalibrate all members of type @c Time . You
   *         may also want to define the assignment operator.
   *       - If Parameters_ contained members that cannot copy themselves, such
   *         as C-style arrays, you need to define the copy constructor and
   *         assignment operator to copy those members.
  **/
  struct Parameters_
  {    
    //! membrane parameters (unchanged from mat2_psc_exp) 
    //!  Membrane time constant (Yamauchi et al. explicitly states to use 10 ms)
    double tau_m;
    //!  Capacitance of the membrane
    double C_m;
    //!  Duration of refractory period
    double refr_T;
    //!  Resting potential
    double E_L;
    //!  Time constant of postsynaptic excitatory currents
    double tau_syn_exc;
    //!  Time constant of postsynaptic inhibitory currents
    double tau_syn_inh;
    //! spike-history threshold parameters (unchanged from mat2_psc_exp) 
    //!  Short time constant of adaptive threshold
    double tau_1;
    //!  Long time constant of adaptive threshold
    double tau_2;
    //!  Amplitude of short time threshold adaptation [3]
    double alpha_1;
    //!  Amplitude of long time threshold adaptation [4]
    double alpha_2;
    //!  This value is relative to E_L (resting spike offset) 
    double omega;
    //! voltage-dependent threshold parameters (new, AMAT extension) 
    //!  Timescale of the voltage-dependency kernel K(s)=s*exp(-s/tau_v) [4]
    double tau_v;
    //!  Strength/sign of voltage dependency. beta=0 recovers mat2_psc_exp
    double beta;
    //!  constant external input current
    double I_e;

    /**
     * Initialize parameters to their default values.
    **/
    Parameters_();
  };

  /**
   * Dynamic state of the neuron.
   *
   *
   *
   * These are the state variables that are advanced in time by calls to
   * @c update(). In many models, some or all of them can be set by the user
   * through @c `node.set()`. The state variables are initialized from the model
   * prototype when the node is created. State variables are reset by @c ResetNetwork.
   *
   * @note State_ need neither copy constructor nor @c operator=(), since
   *       all its members are copied properly by the default copy constructor
   *       and assignment operator. Important:
   *       - If State_ contained @c Time members, you need to define the
   *         assignment operator to recalibrate all members of type @c Time . You
   *         may also want to define the assignment operator.
   *       - If State_ contained members that cannot copy themselves, such
   *         as C-style arrays, you need to define the copy constructor and
   *         assignment operator to copy those members.
  **/
  struct State_
  {    
    //! spike-history threshold (oringal MAT neuronal model)
    //!  theta_1(t): short-timescale spike-history threshold
    double V_th_alpha_1;
    //!  theta_2(t): long-timescale spike-history threshold
    double V_th_alpha_2;
    //! voltage-dependent threshold (AMAT extension)
    //!  theta_V(t): voltage-dependent threshold term
    double V_th_v;
    //!  Auxiliary variable w = dtheta_V/dt + theta_V/tau_V,
    double V_th_v_aux;
    //! needed to express the alpha-kernel convolution as two
    //! coupled first-order ODEs instead of one 2nd-order ODE. 
    //! membrane potential and refractory timer 
    //!  Absolute membrane potential; never reset on spike
    double V_m;
    //!  Refractory period timer; counts down to 0 after a spike
    double refr_t;
    double I_kernel_inh__X__inh_spikes;
    double I_kernel_exc__X__exc_spikes;

    State_();
  };

  struct DelayedVariables_
  {
  };

  /**
   * Internal variables of the neuron.
   *
   *
   *
   * These variables must be initialized by @c pre_run_hook (or calibrate in NEST 3.3 and older), which is called before
   * the first call to @c update() upon each call to @c Simulate.
   * @node Variables_ needs neither constructor, copy constructor or assignment operator,
   *       since it is initialized by @c pre_run_hook() (or calibrate() in NEST 3.3 and older). If Variables_ has members that
   *       cannot destroy themselves, Variables_ will need a destructor.
  **/
  struct Variables_
  {
    //!  Unitary postsynaptic current amplitude
    double unit_psc;
    double __h;
    double __ode_cse_prop_0;
    double __ode_cse_prop_1;
    double __ode_cse_prop_2;
    double __ode_cse_prop_3;
    double __ode_cse_prop_4;
    double __ode_cse_prop_5;
    double __ode_cse_prop_6;
    double __ode_cse_prop_7;
    double __ode_cse_prop_8;
    double __ode_cse_prop_9;
    double __ode_cse_prop_10;
    double __ode_cse_prop_11;
    double __ode_cse_prop_12;
    double __ode_cse_prop_13;
    double __ode_cse_prop_14;
    double __ode_cse_prop_15;
    double __ode_cse_prop_16;
    double __ode_cse_prop_17;
    double __ode_cse_prop_18;
    double __ode_cse_prop_19;
    double __ode_cse_prop_20;
    double __ode_cse_prop_21;
    double __ode_cse_prop_22;
    double __ode_cse_prop_23;
    double __ode_cse_prop_24;
    double __ode_cse_prop_25;
    double __ode_cse_prop_26;
    double __ode_cse_prop_27;
    double __ode_cse_prop_28;
    double __ode_cse_prop_29;
    double __ode_cse_prop_30;
    double __ode_cse_prop_31;
    double __ode_cse_prop_32;
    double __ode_cse_prop_33;
    double __ode_cse_prop_34;
    double __ode_cse_prop_35;
    double __ode_cse_prop_36;
    double __ode_cse_prop_37;
    double __ode_cse_prop_38;
    double __ode_cse_prop_39;
    double __ode_cse_prop_40;
    double __ode_cse_prop_41;
    double __ode_cse_prop_42;
    double __ode_cse_prop_43;
    double __ode_cse_prop_44;
    double __ode_cse_prop_45;
    double __ode_cse_prop_46;
    double __ode_cse_prop_47;
    double __ode_cse_prop_48;
    double __ode_cse_prop_49;
    double __ode_cse_prop_50;
    double __ode_cse_prop_51;
    double __ode_cse_prop_52;
    double __ode_cse_prop_53;
    double __ode_cse_prop_54;
    double __ode_cse_prop_55;
    double __ode_cse_prop_56;
    double __ode_cse_prop_57;
    double __ode_cse_prop_58;
    double __ode_cse_prop_59;
    double __ode_cse_prop_60;
    double __ode_cse_prop_61;
    double __ode_cse_prop_62;
    double __ode_cse_prop_63;
    double __ode_cse_prop_64;
    double __ode_cse_prop_65;
    double __ode_cse_prop_66;
    double __ode_cse_prop_67;
    double __ode_cse_prop_68;
    double __ode_cse_prop_69;
    double __ode_cse_prop_70;
    double __ode_cse_prop_71;
    double __ode_cse_prop_72;
    double __ode_cse_prop_73;
    double __ode_cse_prop_74;
    double __ode_cse_prop_75;
    double __ode_cse_prop_76;
    double __ode_cse_prop_77;
    double __P__V_th_alpha_1__V_th_alpha_1;
    double __P__V_th_alpha_2__V_th_alpha_2;
    double __P__V_m__V_m;
    double __P__V_m__I_kernel_inh__X__inh_spikes;
    double __P__V_m__I_kernel_exc__X__exc_spikes;
    double __P__V_th_v_aux__V_m;
    double __P__V_th_v_aux__V_th_v_aux;
    double __P__V_th_v_aux__I_kernel_inh__X__inh_spikes;
    double __P__V_th_v_aux__I_kernel_exc__X__exc_spikes;
    double __P__V_th_v__V_m;
    double __P__V_th_v__V_th_v_aux;
    double __P__V_th_v__V_th_v;
    double __P__V_th_v__I_kernel_inh__X__inh_spikes;
    double __P__V_th_v__I_kernel_exc__X__exc_spikes;
    double __P__refr_t__refr_t;
    double __P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes;
    double __P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes;
  };

  /**
   * Buffers of the neuron.
   * Usually buffers for incoming spikes and data logged for analog recorders.
   * Buffers must be initialized by @c init_buffers_(), which is called before
   * @c pre_run_hook() (or calibrate() in NEST 3.3 and older) on the first call to @c Simulate after the start of NEST,
   * ResetKernel or ResetNetwork.
   * @node Buffers_ needs neither constructor, copy constructor or assignment operator,
   *       since it is initialized by @c init_nodes_(). If Buffers_ has members that
   *       cannot destroy themselves, Buffers_ will need a destructor.
  **/
  struct Buffers_
  {
    Buffers_(amat_neuron_nestml &);
    Buffers_(const Buffers_ &, amat_neuron_nestml &);

    /**
     * Logger for all analog data
    **/
    nest::UniversalDataLogger<amat_neuron_nestml> logger_;

    // -----------------------------------------------------------------------
    //   Spike buffers and sums of incoming spikes/currents per timestep
    // -----------------------------------------------------------------------    



    /**
     * Buffer containing the incoming spikes
    **/
    inline std::vector< nest::RingBuffer >& get_spike_inputs_()
    {
        return spike_inputs_;
    }
    std::vector< nest::RingBuffer > spike_inputs_;

    /**
     * Buffer containing the sum of all the incoming spikes
    **/
    inline std::vector< double >& get_spike_inputs_grid_sum_()
    {
        return spike_inputs_grid_sum_;
    }
    std::vector< double > spike_inputs_grid_sum_;

    /**
     * Buffer containing a flag whether incoming spikes have been received on a given port
    **/
    inline std::vector< nest::RingBuffer >& get_spike_input_received_()
    {
        return spike_input_received_;
    }
    std::vector< nest::RingBuffer > spike_input_received_;

    /**
     * Buffer containing a flag whether incoming spikes have been received on a given port
    **/
    inline std::vector< double >& get_spike_input_received_grid_sum_()
    {
        return spike_input_received_grid_sum_;
    }
    std::vector< double > spike_input_received_grid_sum_;

    // -----------------------------------------------------------------------
    //   Continuous-input buffers
    // -----------------------------------------------------------------------

    




    /**
     * Buffer containing the incoming continuous input
    **/
    inline std::vector< nest::RingBuffer >& get_continuous_inputs_()
    {
        return continuous_inputs_;
    }
    std::vector< nest::RingBuffer > continuous_inputs_;

    /**
     * Buffer containing the sum of all the continuous inputs
    **/
    inline std::vector< double >& get_continuous_inputs_grid_sum_()
    {
        return continuous_inputs_grid_sum_;
    }
    std::vector< double > continuous_inputs_grid_sum_;
  };

  // -------------------------------------------------------------------------
  //   Getters for inline expressions
  // -------------------------------------------------------------------------
public:
  inline double get_I_syn_ex() const
  {
    return (V_.unit_psc * S_.I_kernel_exc__X__exc_spikes);
  }

  inline double get_I_syn_in() const
  {
    return ((-V_.unit_psc) * S_.I_kernel_inh__X__inh_spikes);
  }

  inline double get_I_syn() const
  {
    return ((V_.unit_psc * S_.I_kernel_exc__X__exc_spikes)) + (((-V_.unit_psc) * S_.I_kernel_inh__X__inh_spikes));
  }

  inline double get_dV_dt() const
  {
    return (-(S_.V_m - P_.E_L)) / P_.tau_m + ((((V_.unit_psc * S_.I_kernel_exc__X__exc_spikes)) + (((-V_.unit_psc) * S_.I_kernel_inh__X__inh_spikes))) + P_.I_e + B_.continuous_inputs_grid_sum_[I_STIM]) / P_.C_m;
  }

  inline double get_V_th() const
  {
    return (P_.omega + S_.V_th_alpha_1 + S_.V_th_alpha_2 + S_.V_th_v);
  }



  // -------------------------------------------------------------------------
  //   Setters for inline expressions (this is allowed for expressions containing a convolve() call)
  // -------------------------------------------------------------------------
private:
  











  // -------------------------------------------------------------------------
  //   Getters/setters for input buffers
  // -------------------------------------------------------------------------  




  /**
   * Buffer containing the incoming spikes
  **/
  inline std::vector< nest::RingBuffer >& get_spike_inputs_()
  {
      return B_.get_spike_inputs_();
  }

  /**
   * Buffer containing the sum of all the incoming spikes
  **/
  inline std::vector< double >& get_spike_inputs_grid_sum_()
  {
      return B_.get_spike_inputs_grid_sum_();
  }

  /**
   * Buffer containing a flag whether incoming spikes have been received on a given port
  **/
  inline std::vector< nest::RingBuffer >& get_spike_input_received_()
  {
      return B_.get_spike_input_received_();
  }

  /**
   * Buffer containing a flag whether incoming spikes have been received on a given port
  **/
  inline std::vector< double >& get_spike_input_received_grid_sum_()
  {
      return B_.get_spike_input_received_grid_sum_();
  }




  /**
   * Buffer containing the incoming continuous input
  **/
  inline std::vector< nest::RingBuffer >& get_continuous_inputs_()
  {
      return B_.get_continuous_inputs_();
  }

  /**
   * Buffer containing the sum of all the continuous inputs
  **/
  inline std::vector< double >& get_continuous_inputs_grid_sum_()
  {
      return B_.get_continuous_inputs_grid_sum_();
  }

  // -------------------------------------------------------------------------
  //   Member variables of neuron model.
  //   Each model neuron should have precisely the following four data members,
  //   which are one instance each of the parameters, state, buffers and variables
  //   structures. Experience indicates that the state and variables member should
  //   be next to each other to achieve good efficiency (caching).
  //   Note: Devices require one additional data member, an instance of the
  //   ``Device`` child class they belong to.
  // -------------------------------------------------------------------------


  Parameters_       P_;        //!< Free parameters.
  State_            S_;        //!< Dynamic state.
  DelayedVariables_ DV_;       //!< Delayed state variables.
  Variables_        V_;        //!< Internal Variables
  Buffers_          B_;        //!< Buffers.

  //! Mapping of recordables names to access functions
  static nest::RecordablesMap<amat_neuron_nestml> recordablesMap_;

}; /* neuron amat_neuron_nestml */

inline nest_port_t amat_neuron_nestml::send_test_event(nest::Node& target, nest_rport_t receptor_type, nest::synindex, bool)
{
  // You should usually not change the code in this function.
  // It confirms that the target of connection @c c accepts @c nest::SpikeEvent on
  // the given @c receptor_type.
  nest::SpikeEvent e;
  e.set_sender(*this);
  return target.handles_test_event(e, receptor_type);
}

inline nest_port_t amat_neuron_nestml::handles_test_event(nest::SpikeEvent&, nest_port_t receptor_type)
{
    // You should usually not change the code in this function.
    // It confirms to the connection management system that we are able
    // to handle @c SpikeEvent on port 0. You need to extend the function
    // if you want to differentiate between input ports.
    if (receptor_type != 0)
    {
      throw nest::UnknownReceptorType(receptor_type, get_name());
    }
    return 0;
}

inline nest_port_t amat_neuron_nestml::handles_test_event(nest::CurrentEvent&, nest_port_t receptor_type)
{
  // You should usually not change the code in this function.
  // It confirms to the connection management system that we are able
  // to handle @c CurrentEvent on port 0. You need to extend the function
  // if you want to differentiate between input ports.
  if (receptor_type >= NUM_CONTINUOUS_INPUT_PORTS)
  {
    throw nest::UnknownReceptorType(receptor_type, get_name());
  }
  return receptor_type;
}

inline nest_port_t amat_neuron_nestml::handles_test_event(nest::DataLoggingRequest& dlr, nest_port_t receptor_type)
{
  // You should usually not change the code in this function.
  // It confirms to the connection management system that we are able
  // to handle @c DataLoggingRequest on port 0.
  // The function also tells the built-in UniversalDataLogger that this node
  // is recorded from and that it thus needs to collect data during simulation.
  if (receptor_type != 0)
  {
    throw nest::UnknownReceptorType(receptor_type, get_name());
  }

  return B_.logger_.connect_logging_device(dlr, recordablesMap_);
}

inline void amat_neuron_nestml::get_status(DictionaryDatum&__d) const
{
  // parameters

  def< double >(__d, nest::amat_neuron_nestml_names::_tau_m, get_tau_m());

  def< double >(__d, nest::amat_neuron_nestml_names::_C_m, get_C_m());

  def< double >(__d, nest::amat_neuron_nestml_names::_refr_T, get_refr_T());

  def< double >(__d, nest::amat_neuron_nestml_names::_E_L, get_E_L());

  def< double >(__d, nest::amat_neuron_nestml_names::_tau_syn_exc, get_tau_syn_exc());

  def< double >(__d, nest::amat_neuron_nestml_names::_tau_syn_inh, get_tau_syn_inh());

  def< double >(__d, nest::amat_neuron_nestml_names::_tau_1, get_tau_1());

  def< double >(__d, nest::amat_neuron_nestml_names::_tau_2, get_tau_2());

  def< double >(__d, nest::amat_neuron_nestml_names::_alpha_1, get_alpha_1());

  def< double >(__d, nest::amat_neuron_nestml_names::_alpha_2, get_alpha_2());

  def< double >(__d, nest::amat_neuron_nestml_names::_omega, get_omega());

  def< double >(__d, nest::amat_neuron_nestml_names::_tau_v, get_tau_v());

  def< double >(__d, nest::amat_neuron_nestml_names::_beta, get_beta());

  def< double >(__d, nest::amat_neuron_nestml_names::_I_e, get_I_e());

  // internals

  def< double >(__d, nest::amat_neuron_nestml_names::_unit_psc, get_unit_psc());

  def< double >(__d, nest::amat_neuron_nestml_names::___h, get___h());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_0, get___ode_cse_prop_0());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_1, get___ode_cse_prop_1());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_2, get___ode_cse_prop_2());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_3, get___ode_cse_prop_3());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_4, get___ode_cse_prop_4());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_5, get___ode_cse_prop_5());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_6, get___ode_cse_prop_6());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_7, get___ode_cse_prop_7());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_8, get___ode_cse_prop_8());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_9, get___ode_cse_prop_9());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_10, get___ode_cse_prop_10());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_11, get___ode_cse_prop_11());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_12, get___ode_cse_prop_12());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_13, get___ode_cse_prop_13());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_14, get___ode_cse_prop_14());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_15, get___ode_cse_prop_15());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_16, get___ode_cse_prop_16());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_17, get___ode_cse_prop_17());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_18, get___ode_cse_prop_18());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_19, get___ode_cse_prop_19());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_20, get___ode_cse_prop_20());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_21, get___ode_cse_prop_21());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_22, get___ode_cse_prop_22());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_23, get___ode_cse_prop_23());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_24, get___ode_cse_prop_24());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_25, get___ode_cse_prop_25());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_26, get___ode_cse_prop_26());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_27, get___ode_cse_prop_27());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_28, get___ode_cse_prop_28());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_29, get___ode_cse_prop_29());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_30, get___ode_cse_prop_30());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_31, get___ode_cse_prop_31());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_32, get___ode_cse_prop_32());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_33, get___ode_cse_prop_33());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_34, get___ode_cse_prop_34());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_35, get___ode_cse_prop_35());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_36, get___ode_cse_prop_36());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_37, get___ode_cse_prop_37());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_38, get___ode_cse_prop_38());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_39, get___ode_cse_prop_39());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_40, get___ode_cse_prop_40());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_41, get___ode_cse_prop_41());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_42, get___ode_cse_prop_42());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_43, get___ode_cse_prop_43());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_44, get___ode_cse_prop_44());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_45, get___ode_cse_prop_45());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_46, get___ode_cse_prop_46());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_47, get___ode_cse_prop_47());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_48, get___ode_cse_prop_48());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_49, get___ode_cse_prop_49());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_50, get___ode_cse_prop_50());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_51, get___ode_cse_prop_51());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_52, get___ode_cse_prop_52());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_53, get___ode_cse_prop_53());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_54, get___ode_cse_prop_54());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_55, get___ode_cse_prop_55());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_56, get___ode_cse_prop_56());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_57, get___ode_cse_prop_57());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_58, get___ode_cse_prop_58());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_59, get___ode_cse_prop_59());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_60, get___ode_cse_prop_60());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_61, get___ode_cse_prop_61());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_62, get___ode_cse_prop_62());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_63, get___ode_cse_prop_63());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_64, get___ode_cse_prop_64());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_65, get___ode_cse_prop_65());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_66, get___ode_cse_prop_66());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_67, get___ode_cse_prop_67());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_68, get___ode_cse_prop_68());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_69, get___ode_cse_prop_69());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_70, get___ode_cse_prop_70());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_71, get___ode_cse_prop_71());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_72, get___ode_cse_prop_72());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_73, get___ode_cse_prop_73());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_74, get___ode_cse_prop_74());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_75, get___ode_cse_prop_75());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_76, get___ode_cse_prop_76());

  def< double >(__d, nest::amat_neuron_nestml_names::___ode_cse_prop_77, get___ode_cse_prop_77());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__V_th_alpha_1__V_th_alpha_1, get___P__V_th_alpha_1__V_th_alpha_1());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__V_th_alpha_2__V_th_alpha_2, get___P__V_th_alpha_2__V_th_alpha_2());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__V_m__V_m, get___P__V_m__V_m());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__V_m__I_kernel_inh__X__inh_spikes, get___P__V_m__I_kernel_inh__X__inh_spikes());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__V_m__I_kernel_exc__X__exc_spikes, get___P__V_m__I_kernel_exc__X__exc_spikes());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__V_th_v_aux__V_m, get___P__V_th_v_aux__V_m());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__V_th_v_aux__V_th_v_aux, get___P__V_th_v_aux__V_th_v_aux());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__V_th_v_aux__I_kernel_inh__X__inh_spikes, get___P__V_th_v_aux__I_kernel_inh__X__inh_spikes());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__V_th_v_aux__I_kernel_exc__X__exc_spikes, get___P__V_th_v_aux__I_kernel_exc__X__exc_spikes());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__V_th_v__V_m, get___P__V_th_v__V_m());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__V_th_v__V_th_v_aux, get___P__V_th_v__V_th_v_aux());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__V_th_v__V_th_v, get___P__V_th_v__V_th_v());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__V_th_v__I_kernel_inh__X__inh_spikes, get___P__V_th_v__I_kernel_inh__X__inh_spikes());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__V_th_v__I_kernel_exc__X__exc_spikes, get___P__V_th_v__I_kernel_exc__X__exc_spikes());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__refr_t__refr_t, get___P__refr_t__refr_t());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes, get___P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes());

  def< double >(__d, nest::amat_neuron_nestml_names::___P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes, get___P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes());

  // initial values for state variables in ODE or kernel

  def< double >(__d, nest::amat_neuron_nestml_names::_V_th_alpha_1, get_V_th_alpha_1());

  def< double >(__d, nest::amat_neuron_nestml_names::_V_th_alpha_2, get_V_th_alpha_2());

  def< double >(__d, nest::amat_neuron_nestml_names::_V_th_v, get_V_th_v());

  def< double >(__d, nest::amat_neuron_nestml_names::_V_th_v_aux, get_V_th_v_aux());

  def< double >(__d, nest::amat_neuron_nestml_names::_V_m, get_V_m());

  def< double >(__d, nest::amat_neuron_nestml_names::_refr_t, get_refr_t());

  def< double >(__d, nest::amat_neuron_nestml_names::_I_kernel_inh__X__inh_spikes, get_I_kernel_inh__X__inh_spikes());

  def< double >(__d, nest::amat_neuron_nestml_names::_I_kernel_exc__X__exc_spikes, get_I_kernel_exc__X__exc_spikes());

  StructuralPlasticityNode::get_status( __d );

  
def< ArrayDatum >(__d, nest::names::recordables, recordablesMap_.get_list());
}

inline void amat_neuron_nestml::set_status(const DictionaryDatum&__d)
{
  // parameters
  double tmp_tau_m = get_tau_m();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_tau_m, tmp_tau_m, this);
  double tmp_C_m = get_C_m();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_C_m, tmp_C_m, this);
  double tmp_refr_T = get_refr_T();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_refr_T, tmp_refr_T, this);
  double tmp_E_L = get_E_L();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_E_L, tmp_E_L, this);
  double tmp_tau_syn_exc = get_tau_syn_exc();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_tau_syn_exc, tmp_tau_syn_exc, this);
  double tmp_tau_syn_inh = get_tau_syn_inh();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_tau_syn_inh, tmp_tau_syn_inh, this);
  double tmp_tau_1 = get_tau_1();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_tau_1, tmp_tau_1, this);
  double tmp_tau_2 = get_tau_2();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_tau_2, tmp_tau_2, this);
  double tmp_alpha_1 = get_alpha_1();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_alpha_1, tmp_alpha_1, this);
  double tmp_alpha_2 = get_alpha_2();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_alpha_2, tmp_alpha_2, this);
  double tmp_omega = get_omega();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_omega, tmp_omega, this);
  double tmp_tau_v = get_tau_v();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_tau_v, tmp_tau_v, this);
  double tmp_beta = get_beta();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_beta, tmp_beta, this);
  double tmp_I_e = get_I_e();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_I_e, tmp_I_e, this);

  // initial values for state variables in ODE or kernel
  double tmp_V_th_alpha_1 = get_V_th_alpha_1();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_V_th_alpha_1, tmp_V_th_alpha_1, this);
  double tmp_V_th_alpha_2 = get_V_th_alpha_2();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_V_th_alpha_2, tmp_V_th_alpha_2, this);
  double tmp_V_th_v = get_V_th_v();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_V_th_v, tmp_V_th_v, this);
  double tmp_V_th_v_aux = get_V_th_v_aux();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_V_th_v_aux, tmp_V_th_v_aux, this);
  double tmp_V_m = get_V_m();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_V_m, tmp_V_m, this);
  double tmp_refr_t = get_refr_t();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_refr_t, tmp_refr_t, this);
  double tmp_I_kernel_inh__X__inh_spikes = get_I_kernel_inh__X__inh_spikes();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_I_kernel_inh__X__inh_spikes, tmp_I_kernel_inh__X__inh_spikes, this);
  double tmp_I_kernel_exc__X__exc_spikes = get_I_kernel_exc__X__exc_spikes();
  nest::updateValueParam<double>(__d, nest::amat_neuron_nestml_names::_I_kernel_exc__X__exc_spikes, tmp_I_kernel_exc__X__exc_spikes, this);

  // We now know that (ptmp, stmp) are consistent. We do not
  // write them back to (P_, S_) before we are also sure that
  // the properties to be set in the parent class are internally
  // consistent.
  StructuralPlasticityNode::set_status(__d);

  // if we get here, temporaries contain consistent set of properties
  set_tau_m(tmp_tau_m);
  set_C_m(tmp_C_m);
  set_refr_T(tmp_refr_T);
  set_E_L(tmp_E_L);
  set_tau_syn_exc(tmp_tau_syn_exc);
  set_tau_syn_inh(tmp_tau_syn_inh);
  set_tau_1(tmp_tau_1);
  set_tau_2(tmp_tau_2);
  set_alpha_1(tmp_alpha_1);
  set_alpha_2(tmp_alpha_2);
  set_omega(tmp_omega);
  set_tau_v(tmp_tau_v);
  set_beta(tmp_beta);
  set_I_e(tmp_I_e);
  set_V_th_alpha_1(tmp_V_th_alpha_1);
  set_V_th_alpha_2(tmp_V_th_alpha_2);
  set_V_th_v(tmp_V_th_v);
  set_V_th_v_aux(tmp_V_th_v_aux);
  set_V_m(tmp_V_m);
  set_refr_t(tmp_refr_t);
  set_I_kernel_inh__X__inh_spikes(tmp_I_kernel_inh__X__inh_spikes);
  set_I_kernel_exc__X__exc_spikes(tmp_I_kernel_exc__X__exc_spikes);





  // recompute internal variables in case they are dependent on parameters or state that might have been updated in this call to set_status()
  recompute_internal_variables();
};



#endif /* #ifndef AMAT_NEURON_NESTML */
