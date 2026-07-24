
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
 *  Generated from NESTML 8.3.0 at time: 2026-07-24 11:16:04.732708
**/
#ifndef AMAT_NEURON_NESTML
#define AMAT_NEURON_NESTML

#ifndef HAVE_LIBLTDL
#error "NEST was compiled without support for dynamic loading. Please install libltdl and recompile NEST."
#endif

// C++ includes:
#include <cmath>

#include "config.h"

#ifndef HAVE_GSL
#error "The GSL library is required for the Runge-Kutta solver."
#endif

// External includes:
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

// Includes from nestkernel:
#include "structural_plasticity_node.h"
#include "connection.h"
#include "dict_util.h"
#include "event.h"
#include "nest_types.h"
#include "ring_buffer.h"
#include "universal_data_logger.h"

// uncomment the next line to enable printing of detailed debug information
// #define DEBUG
typedef Dictionary DictionaryDatum;

namespace nest
{
namespace amat_neuron_nestml_names
{
    typedef std::string Name;
    // state variables
    const Name _V_th_alpha_1( "V_th_alpha_1" );
    const Name _V_th_alpha_2( "V_th_alpha_2" );
    const Name _V_th_v( "V_th_v" );
    const Name _V_th_v_aux( "V_th_v_aux" );
    const Name _V_m( "V_m" );
    const Name _refr_t( "refr_t" );
    const Name _I_kernel_exc__X__exc_spikes( "I_kernel_exc__X__exc_spikes" );
    const Name _I_kernel_inh__X__inh_spikes( "I_kernel_inh__X__inh_spikes" );
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
    const Name _tau_V( "tau_V" );
    const Name _beta( "beta" );
    const Name _I_e( "I_e" );
    // internals
    const Name _unit_psc( "unit_psc" );
    const Name ___h( "__h" );
    const Name ___P__V_th_alpha_1__V_th_alpha_1( "__P__V_th_alpha_1__V_th_alpha_1" );
    const Name ___P__V_th_alpha_2__V_th_alpha_2( "__P__V_th_alpha_2__V_th_alpha_2" );
    const Name ___P__V_m__V_m( "__P__V_m__V_m" );
    const Name ___P__V_m__I_kernel_exc__X__exc_spikes( "__P__V_m__I_kernel_exc__X__exc_spikes" );
    const Name ___P__V_m__I_kernel_inh__X__inh_spikes( "__P__V_m__I_kernel_inh__X__inh_spikes" );
    const Name ___P__refr_t__refr_t( "__P__refr_t__refr_t" );
    const Name ___P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes( "__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes" );
    const Name ___P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes( "__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes" );

    const Name gsl_abs_error_tol("gsl_abs_error_tol");
    const Name gsl_rel_error_tol("gsl_rel_error_tol");
}
}



/**
 * Function computing right-hand side of ODE for GSL solver.
 * @note Must be declared here so we can befriend it in class.
 * @note Must have C-linkage for passing to GSL. Internally, it is
 *       a first-class C++ function, but cannot be a member function
 *       because of the C-linkage.
 * @note No point in declaring it inline, since it is called
 *       through a function pointer.
 * @param void* Pointer to model neuron instance.
 *
 * Integrate the variables: refr_t
**/
extern "C" inline int amat_neuron_nestml_dynamics_refr_t( double, const double ode_state[], double f[], void* pnode );
/**
 * Function computing right-hand side of ODE for GSL solver.
 * @note Must be declared here so we can befriend it in class.
 * @note Must have C-linkage for passing to GSL. Internally, it is
 *       a first-class C++ function, but cannot be a member function
 *       because of the C-linkage.
 * @note No point in declaring it inline, since it is called
 *       through a function pointer.
 * @param void* Pointer to model neuron instance.
 *
 * Integrate the variables: V_m_V_th_alpha_1_V_th_alpha_2_V_th_v_V_th_v_aux
**/
extern "C" inline int amat_neuron_nestml_dynamics_V_m_V_th_alpha_1_V_th_alpha_2_V_th_v_V_th_v_aux( double, const double ode_state[], double f[], void* pnode );
/**
 * Function computing right-hand side of ODE for GSL solver.
 * @note Must be declared here so we can befriend it in class.
 * @note Must have C-linkage for passing to GSL. Internally, it is
 *       a first-class C++ function, but cannot be a member function
 *       because of the C-linkage.
 * @note No point in declaring it inline, since it is called
 *       through a function pointer.
 * @param void* Pointer to model neuron instance.
 *
 * Integrate the variables: 
**/
extern "C" inline int amat_neuron_nestml_dynamics( double, const double ode_state[], double f[], void* pnode );

#include "nest_time.h"
  typedef size_t nest_port_t;
  typedef size_t nest_rport_t;

/* BeginDocumentation
  Name: amat_neuron_nestml

  Description:

    

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
alpha_2 [mV]  Amplitude of long time threshold adaptation [3]
omega [mV]  Resting spike threshold (absolute value, not relative to E_L)
tau_V [ms] voltage-dependent threshold parameters (new, AMAT extension) 
 Timescale of the voltage-dependency kernel K(s)=s*exp(-s/tau_V) [4]
beta [1 / ms]  Strength/sign of voltage dependency. beta=0 recovers mat2_psc_exp
I_e [pA] constant external input current


  Dynamic state variables:
V_th_alpha_1 [mV] spike-history threshold (oringal MAT neuronal model)
 theta_1(t): short-timescale spike-history threshold
V_th_alpha_2 [mV]  theta_2(t): long-timescale spike-history threshold
V_th_v [mV] voltage-dependent threshold (AMAT extension)
 theta_V(t): voltage-dependent threshold term
V_th_v_aux [mV / ms]  Auxiliary variable w = dtheta_V/dt + theta_V/tau_V,
V_m [mV] membrane potential and refractory timer 
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
    return S_.ode_state[State_::V_th_alpha_1];
  }inline void set_V_th_alpha_1(const double __v)
  {
    S_.ode_state[State_::V_th_alpha_1] = __v;
  }

  inline double get_V_th_alpha_2() const
  {
    return S_.ode_state[State_::V_th_alpha_2];
  }inline void set_V_th_alpha_2(const double __v)
  {
    S_.ode_state[State_::V_th_alpha_2] = __v;
  }

  inline double get_V_th_v() const
  {
    return S_.ode_state[State_::V_th_v];
  }inline void set_V_th_v(const double __v)
  {
    S_.ode_state[State_::V_th_v] = __v;
  }

  inline double get_V_th_v_aux() const
  {
    return S_.ode_state[State_::V_th_v_aux];
  }inline void set_V_th_v_aux(const double __v)
  {
    S_.ode_state[State_::V_th_v_aux] = __v;
  }

  inline double get_V_m() const
  {
    return S_.ode_state[State_::V_m];
  }inline void set_V_m(const double __v)
  {
    S_.ode_state[State_::V_m] = __v;
  }

  inline double get_refr_t() const
  {
    return S_.ode_state[State_::refr_t];
  }inline void set_refr_t(const double __v)
  {
    S_.ode_state[State_::refr_t] = __v;
  }

  inline double get_I_kernel_exc__X__exc_spikes() const
  {
    return S_.ode_state[State_::I_kernel_exc__X__exc_spikes];
  }inline void set_I_kernel_exc__X__exc_spikes(const double __v)
  {
    S_.ode_state[State_::I_kernel_exc__X__exc_spikes] = __v;
  }

  inline double get_I_kernel_inh__X__inh_spikes() const
  {
    return S_.ode_state[State_::I_kernel_inh__X__inh_spikes];
  }inline void set_I_kernel_inh__X__inh_spikes(const double __v)
  {
    S_.ode_state[State_::I_kernel_inh__X__inh_spikes] = __v;
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

  inline double get_tau_V() const
  {
    return P_.tau_V;
  }inline void set_tau_V(const double __v)
  {
    P_.tau_V = __v;
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
  inline double get___P__V_m__I_kernel_exc__X__exc_spikes() const
  {
    return V_.__P__V_m__I_kernel_exc__X__exc_spikes;
  }inline void set___P__V_m__I_kernel_exc__X__exc_spikes(const double __v)
  {
    V_.__P__V_m__I_kernel_exc__X__exc_spikes = __v;
  }
  inline double get___P__V_m__I_kernel_inh__X__inh_spikes() const
  {
    return V_.__P__V_m__I_kernel_inh__X__inh_spikes;
  }inline void set___P__V_m__I_kernel_inh__X__inh_spikes(const double __v)
  {
    V_.__P__V_m__I_kernel_inh__X__inh_spikes = __v;
  }
  inline double get___P__refr_t__refr_t() const
  {
    return V_.__P__refr_t__refr_t;
  }inline void set___P__refr_t__refr_t(const double __v)
  {
    V_.__P__refr_t__refr_t = __v;
  }
  inline double get___P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes() const
  {
    return V_.__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes;
  }inline void set___P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes(const double __v)
  {
    V_.__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes = __v;
  }
  inline double get___P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes() const
  {
    return V_.__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes;
  }inline void set___P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes(const double __v)
  {
    V_.__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes = __v;
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
    //!  Amplitude of long time threshold adaptation [3]
    double alpha_2;
    //!  Resting spike threshold (absolute value, not relative to E_L)
    double omega;
    //! voltage-dependent threshold parameters (new, AMAT extension) 
    //!  Timescale of the voltage-dependency kernel K(s)=s*exp(-s/tau_V) [4]
    double tau_V;
    //!  Strength/sign of voltage dependency. beta=0 recovers mat2_psc_exp
    double beta;
    //! constant external input current
    double I_e;

    double __gsl_abs_error_tol;
    double __gsl_rel_error_tol;

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

    // non-ODE state variables
    //! Symbolic indices to the elements of the state vector y
    enum StateVecElems
    {
      V_th_alpha_1,
      V_th_alpha_2,
      V_m,
      V_th_v_aux,
      V_th_v,
      refr_t,
      I_kernel_exc__X__exc_spikes,
      I_kernel_inh__X__inh_spikes,
      // moved state variables from synapse (numeric)
      // moved state variables from synapse (analytic)
      // final entry to easily get the vector size
      STATE_VEC_SIZE
    };

    //! state vector, must be C-array for GSL solver
    double ode_state[STATE_VEC_SIZE];

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
    double __P__V_th_alpha_1__V_th_alpha_1;
    double __P__V_th_alpha_2__V_th_alpha_2;
    double __P__V_m__V_m;
    double __P__V_m__I_kernel_exc__X__exc_spikes;
    double __P__V_m__I_kernel_inh__X__inh_spikes;
    double __P__refr_t__refr_t;
    double __P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes;
    double __P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes;
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

    // -----------------------------------------------------------------------
    //   GSL ODE solver data structures
    // -----------------------------------------------------------------------

    gsl_odeiv_step* __s;    //!< stepping function
    gsl_odeiv_control* __c; //!< adaptive stepsize control function
    gsl_odeiv_evolve* __e;  //!< evolution function
    gsl_odeiv_system __sys; //!< struct describing system

    // __integration_step should be reset with the neuron on ResetNetwork,
    // but remain unchanged during calibration. Since it is initialized with
    // step_, and the resolution cannot change after nodes have been created,
    // it is safe to place both here.
    double __step;             //!< step size in ms
    double __integration_step; //!< current integration time step, updated by GSL
  };

  // -------------------------------------------------------------------------
  //   Getters for inline expressions
  // -------------------------------------------------------------------------
public:
  inline double get_I_syn() const
  {
    return V_.unit_psc * (S_.ode_state[State_::I_kernel_exc__X__exc_spikes] - S_.ode_state[State_::I_kernel_inh__X__inh_spikes]);
  }

  inline double get_dV_dt() const
  {
    return (-(S_.ode_state[State_::V_m] - P_.E_L)) / P_.tau_m + ((V_.unit_psc * (S_.ode_state[State_::I_kernel_exc__X__exc_spikes] - S_.ode_state[State_::I_kernel_inh__X__inh_spikes])) + P_.I_e + B_.continuous_inputs_grid_sum_[I_STIM]) / P_.C_m;
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
  friend int amat_neuron_nestml_dynamics_refr_t( double, const double ode_state[], double f[], void* pnode );
  friend int amat_neuron_nestml_dynamics_V_m_V_th_alpha_1_V_th_alpha_2_V_th_v_V_th_v_aux( double, const double ode_state[], double f[], void* pnode );
  friend int amat_neuron_nestml_dynamics( double, const double ode_state[], double f[], void* pnode );

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

  __d[ nest::amat_neuron_nestml_names::_tau_m ] = get_tau_m();

  __d[ nest::amat_neuron_nestml_names::_C_m ] = get_C_m();

  __d[ nest::amat_neuron_nestml_names::_refr_T ] = get_refr_T();

  __d[ nest::amat_neuron_nestml_names::_E_L ] = get_E_L();

  __d[ nest::amat_neuron_nestml_names::_tau_syn_exc ] = get_tau_syn_exc();

  __d[ nest::amat_neuron_nestml_names::_tau_syn_inh ] = get_tau_syn_inh();

  __d[ nest::amat_neuron_nestml_names::_tau_1 ] = get_tau_1();

  __d[ nest::amat_neuron_nestml_names::_tau_2 ] = get_tau_2();

  __d[ nest::amat_neuron_nestml_names::_alpha_1 ] = get_alpha_1();

  __d[ nest::amat_neuron_nestml_names::_alpha_2 ] = get_alpha_2();

  __d[ nest::amat_neuron_nestml_names::_omega ] = get_omega();

  __d[ nest::amat_neuron_nestml_names::_tau_V ] = get_tau_V();

  __d[ nest::amat_neuron_nestml_names::_beta ] = get_beta();

  __d[ nest::amat_neuron_nestml_names::_I_e ] = get_I_e();

  // internals

  __d[ nest::amat_neuron_nestml_names::_unit_psc ] = get_unit_psc();

  __d[ nest::amat_neuron_nestml_names::___h ] = get___h();

  __d[ nest::amat_neuron_nestml_names::___P__V_th_alpha_1__V_th_alpha_1 ] = get___P__V_th_alpha_1__V_th_alpha_1();

  __d[ nest::amat_neuron_nestml_names::___P__V_th_alpha_2__V_th_alpha_2 ] = get___P__V_th_alpha_2__V_th_alpha_2();

  __d[ nest::amat_neuron_nestml_names::___P__V_m__V_m ] = get___P__V_m__V_m();

  __d[ nest::amat_neuron_nestml_names::___P__V_m__I_kernel_exc__X__exc_spikes ] = get___P__V_m__I_kernel_exc__X__exc_spikes();

  __d[ nest::amat_neuron_nestml_names::___P__V_m__I_kernel_inh__X__inh_spikes ] = get___P__V_m__I_kernel_inh__X__inh_spikes();

  __d[ nest::amat_neuron_nestml_names::___P__refr_t__refr_t ] = get___P__refr_t__refr_t();

  __d[ nest::amat_neuron_nestml_names::___P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes ] = get___P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes();

  __d[ nest::amat_neuron_nestml_names::___P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes ] = get___P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes();

  // initial values for state variables in ODE or kernel

  __d[ nest::amat_neuron_nestml_names::_V_th_alpha_1 ] = get_V_th_alpha_1();

  __d[ nest::amat_neuron_nestml_names::_V_th_alpha_2 ] = get_V_th_alpha_2();

  __d[ nest::amat_neuron_nestml_names::_V_th_v ] = get_V_th_v();

  __d[ nest::amat_neuron_nestml_names::_V_th_v_aux ] = get_V_th_v_aux();

  __d[ nest::amat_neuron_nestml_names::_V_m ] = get_V_m();

  __d[ nest::amat_neuron_nestml_names::_refr_t ] = get_refr_t();

  __d[ nest::amat_neuron_nestml_names::_I_kernel_exc__X__exc_spikes ] = get_I_kernel_exc__X__exc_spikes();

  __d[ nest::amat_neuron_nestml_names::_I_kernel_inh__X__inh_spikes ] = get_I_kernel_inh__X__inh_spikes();

  StructuralPlasticityNode::get_status( __d );

  
__d[ nest::names::recordables ] = recordablesMap_.get_list();
  
__d[ nest::amat_neuron_nestml_names::gsl_abs_error_tol ] = P_.__gsl_abs_error_tol;
  if ( P_.__gsl_abs_error_tol <= 0. ){
    throw nest::BadProperty( "The gsl_abs_error_tol must be strictly positive." );
  }
  
__d[ nest::amat_neuron_nestml_names::gsl_rel_error_tol ] = P_.__gsl_rel_error_tol;
  if ( P_.__gsl_rel_error_tol < 0. ){
    throw nest::BadProperty( "The gsl_rel_error_tol must be zero or positive." );
  }
}

inline void amat_neuron_nestml::set_status(const DictionaryDatum&__d)
{
  // parameters
  double tmp_tau_m = get_tau_m();
  update_value_param(__d, nest::amat_neuron_nestml_names::_tau_m, tmp_tau_m, this);
  double tmp_C_m = get_C_m();
  update_value_param(__d, nest::amat_neuron_nestml_names::_C_m, tmp_C_m, this);
  double tmp_refr_T = get_refr_T();
  update_value_param(__d, nest::amat_neuron_nestml_names::_refr_T, tmp_refr_T, this);
  double tmp_E_L = get_E_L();
  update_value_param(__d, nest::amat_neuron_nestml_names::_E_L, tmp_E_L, this);
  double tmp_tau_syn_exc = get_tau_syn_exc();
  update_value_param(__d, nest::amat_neuron_nestml_names::_tau_syn_exc, tmp_tau_syn_exc, this);
  double tmp_tau_syn_inh = get_tau_syn_inh();
  update_value_param(__d, nest::amat_neuron_nestml_names::_tau_syn_inh, tmp_tau_syn_inh, this);
  double tmp_tau_1 = get_tau_1();
  update_value_param(__d, nest::amat_neuron_nestml_names::_tau_1, tmp_tau_1, this);
  double tmp_tau_2 = get_tau_2();
  update_value_param(__d, nest::amat_neuron_nestml_names::_tau_2, tmp_tau_2, this);
  double tmp_alpha_1 = get_alpha_1();
  update_value_param(__d, nest::amat_neuron_nestml_names::_alpha_1, tmp_alpha_1, this);
  double tmp_alpha_2 = get_alpha_2();
  update_value_param(__d, nest::amat_neuron_nestml_names::_alpha_2, tmp_alpha_2, this);
  double tmp_omega = get_omega();
  update_value_param(__d, nest::amat_neuron_nestml_names::_omega, tmp_omega, this);
  double tmp_tau_V = get_tau_V();
  update_value_param(__d, nest::amat_neuron_nestml_names::_tau_V, tmp_tau_V, this);
  double tmp_beta = get_beta();
  update_value_param(__d, nest::amat_neuron_nestml_names::_beta, tmp_beta, this);
  double tmp_I_e = get_I_e();
  update_value_param(__d, nest::amat_neuron_nestml_names::_I_e, tmp_I_e, this);

  // initial values for state variables in ODE or kernel
  double tmp_V_th_alpha_1 = get_V_th_alpha_1();
  update_value_param(__d, nest::amat_neuron_nestml_names::_V_th_alpha_1, tmp_V_th_alpha_1, this);
  double tmp_V_th_alpha_2 = get_V_th_alpha_2();
  update_value_param(__d, nest::amat_neuron_nestml_names::_V_th_alpha_2, tmp_V_th_alpha_2, this);
  double tmp_V_th_v = get_V_th_v();
  update_value_param(__d, nest::amat_neuron_nestml_names::_V_th_v, tmp_V_th_v, this);
  double tmp_V_th_v_aux = get_V_th_v_aux();
  update_value_param(__d, nest::amat_neuron_nestml_names::_V_th_v_aux, tmp_V_th_v_aux, this);
  double tmp_V_m = get_V_m();
  update_value_param(__d, nest::amat_neuron_nestml_names::_V_m, tmp_V_m, this);
  double tmp_refr_t = get_refr_t();
  update_value_param(__d, nest::amat_neuron_nestml_names::_refr_t, tmp_refr_t, this);
  double tmp_I_kernel_exc__X__exc_spikes = get_I_kernel_exc__X__exc_spikes();
  update_value_param(__d, nest::amat_neuron_nestml_names::_I_kernel_exc__X__exc_spikes, tmp_I_kernel_exc__X__exc_spikes, this);
  double tmp_I_kernel_inh__X__inh_spikes = get_I_kernel_inh__X__inh_spikes();
  update_value_param(__d, nest::amat_neuron_nestml_names::_I_kernel_inh__X__inh_spikes, tmp_I_kernel_inh__X__inh_spikes, this);

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
  set_tau_V(tmp_tau_V);
  set_beta(tmp_beta);
  set_I_e(tmp_I_e);
  set_V_th_alpha_1(tmp_V_th_alpha_1);
  set_V_th_alpha_2(tmp_V_th_alpha_2);
  set_V_th_v(tmp_V_th_v);
  set_V_th_v_aux(tmp_V_th_v_aux);
  set_V_m(tmp_V_m);
  set_refr_t(tmp_refr_t);
  set_I_kernel_exc__X__exc_spikes(tmp_I_kernel_exc__X__exc_spikes);
  set_I_kernel_inh__X__inh_spikes(tmp_I_kernel_inh__X__inh_spikes);




  __d.update_value(nest::amat_neuron_nestml_names::gsl_abs_error_tol, P_.__gsl_abs_error_tol);
  if ( P_.__gsl_abs_error_tol <= 0. )
  {
    throw nest::BadProperty( "The gsl_abs_error_tol must be strictly positive." );
  }
  __d.update_value(nest::amat_neuron_nestml_names::gsl_rel_error_tol, P_.__gsl_rel_error_tol);
  if ( P_.__gsl_rel_error_tol < 0. )
  {
    throw nest::BadProperty( "The gsl_rel_error_tol must be zero or positive." );
  }

  // recompute internal variables in case they are dependent on parameters or state that might have been updated in this call to set_status()
  recompute_internal_variables();
};



#endif /* #ifndef AMAT_NEURON_NESTML */
