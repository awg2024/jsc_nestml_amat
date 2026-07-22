
/*
 *  mat2_psc_exp_neuron_nestml.cpp
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
 *  Generated from NESTML 8.3.0 at time: 2026-07-21 12:02:54.122368
**/

// C++ includes:
#include <limits>

// Includes from libnestutil:
#include "numerics.h"

// Includes from nestkernel:
#include "exceptions.h"
#include "kernel_manager.h"
#include "nest_impl.h"
#include "universal_data_logger_impl.h"

#include "mat2_psc_exp_neuron_nestml.h"
void
register_mat2_psc_exp_neuron_nestml( const std::string& name )
{
  nest::register_node_model< mat2_psc_exp_neuron_nestml >( name );
}

// ---------------------------------------------------------------------------
//   Recordables map
// ---------------------------------------------------------------------------
nest::RecordablesMap<mat2_psc_exp_neuron_nestml> mat2_psc_exp_neuron_nestml::recordablesMap_;
namespace nest
{
  // Override the create() method with one call to RecordablesMap::insert_() for each quantity to be recorded.
template <> void RecordablesMap<mat2_psc_exp_neuron_nestml>::create()
  {
    // add state variables to recordables map
    // add state variables to recordables map
    insert_(mat2_psc_exp_neuron_nestml_names::_V_th_alpha_1, &mat2_psc_exp_neuron_nestml::get_V_th_alpha_1);
    insert_(mat2_psc_exp_neuron_nestml_names::_V_th_alpha_2, &mat2_psc_exp_neuron_nestml::get_V_th_alpha_2);
    insert_(mat2_psc_exp_neuron_nestml_names::_V_m, &mat2_psc_exp_neuron_nestml::get_V_m);
    insert_(mat2_psc_exp_neuron_nestml_names::_refr_t, &mat2_psc_exp_neuron_nestml::get_refr_t);
    insert_(mat2_psc_exp_neuron_nestml_names::_I_kernel_exc__X__exc_spikes, &mat2_psc_exp_neuron_nestml::get_I_kernel_exc__X__exc_spikes);
    insert_(mat2_psc_exp_neuron_nestml_names::_I_kernel_inh__X__inh_spikes, &mat2_psc_exp_neuron_nestml::get_I_kernel_inh__X__inh_spikes);
  }
}
std::vector< std::tuple< int, int > > mat2_psc_exp_neuron_nestml::rport_to_nestml_buffer_idx =
{
  
  { mat2_psc_exp_neuron_nestml::EXC_SPIKES, mat2_psc_exp_neuron_nestml::INH_SPIKES },
};

// ---------------------------------------------------------------------------
//   Default constructors defining default parameters and state
//   Note: the implementation is empty. The initialization is of variables
//   is a part of mat2_psc_exp_neuron_nestml's constructor.
// ---------------------------------------------------------------------------

mat2_psc_exp_neuron_nestml::Parameters_::Parameters_()
{
}

mat2_psc_exp_neuron_nestml::State_::State_()
{
}

// ---------------------------------------------------------------------------
//   Parameter and state extractions and manipulation functions
// ---------------------------------------------------------------------------

mat2_psc_exp_neuron_nestml::Buffers_::Buffers_(mat2_psc_exp_neuron_nestml &n):
  logger_(n)
  , spike_inputs_( std::vector< nest::RingBuffer >( NUM_SPIKE_RECEPTORS ) )
  , spike_inputs_grid_sum_( std::vector< double >( NUM_SPIKE_RECEPTORS ) )
  , spike_input_received_( std::vector< nest::RingBuffer >( NUM_SPIKE_RECEPTORS ) )
  , spike_input_received_grid_sum_( std::vector< double >( NUM_SPIKE_RECEPTORS ) )
  , continuous_inputs_( std::vector< nest::RingBuffer >( NUM_CONTINUOUS_INPUT_PORTS ) )
  , continuous_inputs_grid_sum_( std::vector< double >( NUM_CONTINUOUS_INPUT_PORTS ) )
{
  // Initialization of the remaining members is deferred to init_buffers_().
}

mat2_psc_exp_neuron_nestml::Buffers_::Buffers_(const Buffers_ &, mat2_psc_exp_neuron_nestml &n):
  logger_(n)
  , spike_inputs_( std::vector< nest::RingBuffer >( NUM_SPIKE_RECEPTORS ) )
  , spike_inputs_grid_sum_( std::vector< double >( NUM_SPIKE_RECEPTORS ) )
  , spike_input_received_( std::vector< nest::RingBuffer >( NUM_SPIKE_RECEPTORS ) )
  , spike_input_received_grid_sum_( std::vector< double >( NUM_SPIKE_RECEPTORS ) )
  , continuous_inputs_( std::vector< nest::RingBuffer >( NUM_CONTINUOUS_INPUT_PORTS ) )
  , continuous_inputs_grid_sum_( std::vector< double >( NUM_CONTINUOUS_INPUT_PORTS ) )
{
  // Initialization of the remaining members is deferred to init_buffers_().
}

// ---------------------------------------------------------------------------
//   Default constructor for node
// ---------------------------------------------------------------------------

mat2_psc_exp_neuron_nestml::mat2_psc_exp_neuron_nestml():StructuralPlasticityNode(), P_(), S_(), B_(*this)
{
  init_state_internal_();
  recordablesMap_.create();
  pre_run_hook();
}

// ---------------------------------------------------------------------------
//   Copy constructor for node
// ---------------------------------------------------------------------------

mat2_psc_exp_neuron_nestml::mat2_psc_exp_neuron_nestml(const mat2_psc_exp_neuron_nestml& __n):
  StructuralPlasticityNode(), P_(__n.P_), S_(__n.S_), B_(__n.B_, *this)
{
  // copy parameter struct P_
  P_.tau_m = __n.P_.tau_m;
  P_.C_m = __n.P_.C_m;
  P_.refr_T = __n.P_.refr_T;
  P_.E_L = __n.P_.E_L;
  P_.tau_syn_exc = __n.P_.tau_syn_exc;
  P_.tau_syn_inh = __n.P_.tau_syn_inh;
  P_.tau_1 = __n.P_.tau_1;
  P_.tau_2 = __n.P_.tau_2;
  P_.alpha_1 = __n.P_.alpha_1;
  P_.alpha_2 = __n.P_.alpha_2;
  P_.omega = __n.P_.omega;
  P_.I_e = __n.P_.I_e;

  // copy state struct S_
  S_.V_th_alpha_1 = __n.S_.V_th_alpha_1;
  S_.V_th_alpha_2 = __n.S_.V_th_alpha_2;
  S_.V_m = __n.S_.V_m;
  S_.refr_t = __n.S_.refr_t;
  S_.I_kernel_exc__X__exc_spikes = __n.S_.I_kernel_exc__X__exc_spikes;
  S_.I_kernel_inh__X__inh_spikes = __n.S_.I_kernel_inh__X__inh_spikes;

  // copy internals V_
  V_.h = __n.V_.h;
  V_.__h = __n.V_.__h;
  V_.P11th = __n.V_.P11th;
  V_.P22th = __n.V_.P22th;
  V_.unit_psc = __n.V_.unit_psc;
  V_.__P__V_m__V_m = __n.V_.__P__V_m__V_m;
  V_.__P__V_m__I_kernel_exc__X__exc_spikes = __n.V_.__P__V_m__I_kernel_exc__X__exc_spikes;
  V_.__P__V_m__I_kernel_inh__X__inh_spikes = __n.V_.__P__V_m__I_kernel_inh__X__inh_spikes;
  V_.__P__refr_t__refr_t = __n.V_.__P__refr_t__refr_t;
  V_.__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes = __n.V_.__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes;
  V_.__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes = __n.V_.__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes;
}

// ---------------------------------------------------------------------------
//   Destructor for node
// ---------------------------------------------------------------------------

mat2_psc_exp_neuron_nestml::~mat2_psc_exp_neuron_nestml()
{
}

// ---------------------------------------------------------------------------
//   Node initialization functions
// ---------------------------------------------------------------------------
void mat2_psc_exp_neuron_nestml::calibrate_time( const nest::TimeConverter& tc )
{
  LOG( nest::VerbosityLevel::WARNING,
    "mat2_psc_exp_neuron_nestml",
    "Simulation resolution has changed. Internal state and parameters of the model have been reset!" );

  init_state_internal_();
}
void mat2_psc_exp_neuron_nestml::init_state_internal_()
{
#ifdef DEBUG
  std::cout << "[neuron " << this << "] mat2_psc_exp_neuron_nestml::init_state_internal_()" << std::endl;
#endif

  const double __timestep = nest::Time::get_resolution().get_ms();  // do not remove, this is necessary for the timestep() function
  // initial values for parameters
  P_.tau_m = 5; // as ms
  P_.C_m = 100; // as pF
  P_.refr_T = 2; // as ms
  P_.E_L = (-70); // as mV
  P_.tau_syn_exc = 1; // as ms
  P_.tau_syn_inh = 3; // as ms
  P_.tau_1 = 10; // as ms
  P_.tau_2 = 200; // as ms
  P_.alpha_1 = 37; // as mV
  P_.alpha_2 = 2; // as mV
  P_.omega = 19; // as mV
  P_.I_e = 0; // as pA

  V_.__h = nest::Time::get_resolution().get_ms();
  recompute_internal_variables();
  // initial values for state variables
  S_.V_th_alpha_1 = 0; // as mV
  S_.V_th_alpha_2 = 0; // as mV
  S_.V_m = P_.E_L; // as mV
  S_.refr_t = 0; // as ms
  S_.I_kernel_exc__X__exc_spikes = 0; // as real
  S_.I_kernel_inh__X__inh_spikes = 0; // as real
}

void mat2_psc_exp_neuron_nestml::init_buffers_()
{
#ifdef DEBUG
  std::cout << "[neuron " << this << "] mat2_psc_exp_neuron_nestml::init_buffers_()" << std::endl;
#endif
  // spike input buffers
  get_spike_inputs_().clear();
  get_spike_inputs_grid_sum_().clear();
  get_spike_input_received_().clear();
  get_spike_input_received_grid_sum_().clear();
  get_continuous_inputs_().clear();
  get_continuous_inputs_grid_sum_().clear();


  B_.logger_.reset();


}

void mat2_psc_exp_neuron_nestml::recompute_internal_variables(bool exclude_timestep)
{
  const double __timestep = nest::Time::get_resolution().get_ms();  // do not remove, this is necessary for the timestep() function

  if (exclude_timestep)
  {    
    V_.h = nest::Time::get_resolution().get_ms(); // as ms
    V_.P11th = std::exp((-V_.h) / P_.tau_1); // as real
    V_.P22th = std::exp((-V_.h) / P_.tau_2); // as real
    V_.unit_psc = 1; // as pA
    V_.__P__V_m__V_m = std::exp((-V_.__h) / P_.tau_m); // as real
    V_.__P__V_m__I_kernel_exc__X__exc_spikes = P_.tau_m * P_.tau_syn_exc * V_.unit_psc * ((-std::exp(V_.__h / P_.tau_m)) + std::exp(V_.__h / P_.tau_syn_exc)) * std::exp((-V_.__h) * (P_.tau_m + P_.tau_syn_exc) / (P_.tau_m * P_.tau_syn_exc)) / (P_.C_m * (P_.tau_m - P_.tau_syn_exc)); // as real
    V_.__P__V_m__I_kernel_inh__X__inh_spikes = P_.tau_m * P_.tau_syn_inh * V_.unit_psc * (std::exp(V_.__h / P_.tau_m) - std::exp(V_.__h / P_.tau_syn_inh)) * std::exp((-V_.__h) * (P_.tau_m + P_.tau_syn_inh) / (P_.tau_m * P_.tau_syn_inh)) / (P_.C_m * (P_.tau_m - P_.tau_syn_inh)); // as real
    V_.__P__refr_t__refr_t = 1; // as real
    V_.__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes = std::exp((-V_.__h) / P_.tau_syn_exc); // as real
    V_.__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes = std::exp((-V_.__h) / P_.tau_syn_inh); // as real
  }
  else {    
    V_.h = nest::Time::get_resolution().get_ms(); // as ms
    V_.__h = nest::Time::get_resolution().get_ms(); // as ms
    V_.P11th = std::exp((-V_.h) / P_.tau_1); // as real
    V_.P22th = std::exp((-V_.h) / P_.tau_2); // as real
    V_.unit_psc = 1; // as pA
    V_.__P__V_m__V_m = std::exp((-V_.__h) / P_.tau_m); // as real
    V_.__P__V_m__I_kernel_exc__X__exc_spikes = P_.tau_m * P_.tau_syn_exc * V_.unit_psc * ((-std::exp(V_.__h / P_.tau_m)) + std::exp(V_.__h / P_.tau_syn_exc)) * std::exp((-V_.__h) * (P_.tau_m + P_.tau_syn_exc) / (P_.tau_m * P_.tau_syn_exc)) / (P_.C_m * (P_.tau_m - P_.tau_syn_exc)); // as real
    V_.__P__V_m__I_kernel_inh__X__inh_spikes = P_.tau_m * P_.tau_syn_inh * V_.unit_psc * (std::exp(V_.__h / P_.tau_m) - std::exp(V_.__h / P_.tau_syn_inh)) * std::exp((-V_.__h) * (P_.tau_m + P_.tau_syn_inh) / (P_.tau_m * P_.tau_syn_inh)) / (P_.C_m * (P_.tau_m - P_.tau_syn_inh)); // as real
    V_.__P__refr_t__refr_t = 1; // as real
    V_.__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes = std::exp((-V_.__h) / P_.tau_syn_exc); // as real
    V_.__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes = std::exp((-V_.__h) / P_.tau_syn_inh); // as real
  }
}
void mat2_psc_exp_neuron_nestml::pre_run_hook()
{
#ifdef DEBUG
  std::cout << "[neuron " << this << "] mat2_psc_exp_neuron_nestml::pre_run_hook()" << std::endl;
#endif

  B_.logger_.init();

  // parameters might have changed -- recompute internals
  V_.__h = nest::Time::get_resolution().get_ms();
  recompute_internal_variables();

  // buffers B_
  B_.spike_inputs_.resize(NUM_SPIKE_RECEPTORS);
  B_.spike_inputs_grid_sum_.resize(NUM_SPIKE_RECEPTORS);
  B_.spike_input_received_.resize(NUM_SPIKE_RECEPTORS);
  B_.spike_input_received_grid_sum_.resize(NUM_SPIKE_RECEPTORS);
  B_.continuous_inputs_.resize(NUM_CONTINUOUS_INPUT_PORTS);
  B_.continuous_inputs_grid_sum_.resize(NUM_CONTINUOUS_INPUT_PORTS);

}

// ---------------------------------------------------------------------------
//   Update and spike handling functions
// ---------------------------------------------------------------------------


void mat2_psc_exp_neuron_nestml::update(nest::Time const & origin, const long from, const long to)
{
  const double __timestep = nest::Time::get_resolution().get_ms();  // do not remove, this is necessary for the timestep() function

  for ( long lag = from ; lag < to ; ++lag )
  {


    auto get_t = [origin, lag](){ return nest::Time( nest::Time::step( origin.get_steps() + lag + 1) ).get_ms(); };

#ifdef DEBUG
    std::cout << "[neuron " << this << "] mat2_psc_exp_neuron_nestml::update: handling post spike at t = " << get_t() << std::endl;
#endif
    /**
     * buffer spikes from spiking input ports
    **/

    for (long i = 0; i < NUM_SPIKE_RECEPTORS; ++i)
    {
      get_spike_inputs_grid_sum_()[i] = get_spike_inputs_()[i].get_value(lag);
      get_spike_input_received_grid_sum_()[i] = get_spike_input_received_()[i].get_value(lag);
    }

    /**
     * subthreshold updates of the convolution variables
     *
     * step 1: regardless of whether and how integrate_odes() will be called, update variables due to convolutions
    **/

    const double I_kernel_exc__X__exc_spikes__tmp_ = S_.I_kernel_exc__X__exc_spikes * V_.__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes;
    const double I_kernel_inh__X__inh_spikes__tmp_ = S_.I_kernel_inh__X__inh_spikes * V_.__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes;


    /**
     * Begin NESTML generated code for the update block(s)
    **/

  if (S_.refr_t > 0)
  {  

    // start rendered code for integrate_odes(refr_t)

    // analytic solver: integrating state variables (first step): refr_t
    const double refr_t__tmp = V_.__P__refr_t__refr_t * S_.refr_t - 1. * V_.__h;
    // analytic solver: integrating state variables (second step): refr_t
    /* replace analytically solvable variables with precisely integrated values  */
    S_.refr_t = refr_t__tmp;
  }
  else
  {  
    S_.V_th_alpha_1 = S_.V_th_alpha_1 * V_.P11th;
    S_.V_th_alpha_2 = S_.V_th_alpha_2 * V_.P22th;

    // start rendered code for integrate_odes(V_m)

    // analytic solver: integrating state variables (first step): V_m
    const double V_m__tmp = (-P_.E_L) * V_.__P__V_m__V_m + P_.E_L + S_.I_kernel_exc__X__exc_spikes * V_.__P__V_m__I_kernel_exc__X__exc_spikes + S_.I_kernel_inh__X__inh_spikes * V_.__P__V_m__I_kernel_inh__X__inh_spikes + S_.V_m * V_.__P__V_m__V_m - P_.I_e * V_.__P__V_m__V_m * P_.tau_m / P_.C_m + P_.I_e * P_.tau_m / P_.C_m - B_.continuous_inputs_grid_sum_[I_STIM] * V_.__P__V_m__V_m * P_.tau_m / P_.C_m + B_.continuous_inputs_grid_sum_[I_STIM] * P_.tau_m / P_.C_m;
    // analytic solver: integrating state variables (second step): V_m
    /* replace analytically solvable variables with precisely integrated values  */
    S_.V_m = V_m__tmp;
  }

    /**
     * Begin NESTML generated code for the onReceive block(s)
    **/


    /**
     * subthreshold updates of the convolution variables
     *
     * step 2: regardless of whether and how integrate_odes() was called, update variables due to convolutions. Set to the updated values at the end of the timestep.
    **/

    S_.I_kernel_exc__X__exc_spikes = I_kernel_exc__X__exc_spikes__tmp_;
    S_.I_kernel_inh__X__inh_spikes = I_kernel_inh__X__inh_spikes__tmp_;

    /**
     * spike updates due to convolutions
    **/

    S_.I_kernel_exc__X__exc_spikes += ((0.001 * B_.spike_inputs_grid_sum_[EXC_SPIKES - MIN_SPIKE_RECEPTOR])) / (1 / 1000.0);
    S_.I_kernel_inh__X__inh_spikes += ((0.001 * B_.spike_inputs_grid_sum_[INH_SPIKES - MIN_SPIKE_RECEPTOR])) / (1 / 1000.0);

    /**
     * Begin NESTML generated code for the onCondition block(s)
    **/

    if (S_.refr_t <= 0 && S_.V_m >= P_.E_L + P_.omega + S_.V_th_alpha_1 + S_.V_th_alpha_2)
    {
      S_.refr_t = P_.refr_T;
      S_.V_th_alpha_1 += P_.alpha_1;
      S_.V_th_alpha_2 += P_.alpha_2;

      // begin generated code for emit_spike() function

      #ifdef DEBUG
      std::cout << "[neuron " << this << "] Emitting a spike at t = " << nest::Time(nest::Time::step(origin.get_steps() + lag + 1)).get_ms() << "\n";
      #endif
      set_spiketime(nest::Time::step(origin.get_steps() + lag + 1));
      nest::SpikeEvent se;
      nest::kernel().event_delivery_manager.send(*this, se, lag);
      // end generated code for emit_spike() function
    }

    /**
     * handle continuous input ports
    **/
    for (long i = 0; i < NUM_CONTINUOUS_INPUT_PORTS; ++i)
    {
      get_continuous_inputs_grid_sum_()[i] = get_continuous_inputs_()[i].get_value(lag);
    }
    // voltage logging
    B_.logger_.record_data(origin.get_steps() + lag);
  }
}

// Do not move this function as inline to h-file. It depends on
// universal_data_logger_impl.h being included here.
void mat2_psc_exp_neuron_nestml::handle(nest::DataLoggingRequest& e)
{
  B_.logger_.handle(e);
}


void mat2_psc_exp_neuron_nestml::handle(nest::SpikeEvent &e)
{
#ifdef DEBUG
  std::cout << "[neuron " << this << "] mat2_psc_exp_neuron_nestml::handle(SpikeEvent)" << std::endl;
#endif

  assert(e.get_delay_steps() > 0);
  assert( e.get_rport() < B_.spike_inputs_.size() );

  double weight = e.get_weight();
  size_t nestml_buffer_idx = 0;
  if ( weight >= 0.0 )
  {
    nestml_buffer_idx = std::get<0>(rport_to_nestml_buffer_idx[e.get_rport()]);
  }
  else
  {
    nestml_buffer_idx = std::get<1>(rport_to_nestml_buffer_idx[e.get_rport()]);
    if ( nestml_buffer_idx == mat2_psc_exp_neuron_nestml::PORT_NOT_AVAILABLE )
    {
      nestml_buffer_idx = std::get<0>(rport_to_nestml_buffer_idx[e.get_rport()]);
    }
    weight = -weight;
  }
  B_.spike_inputs_[ nestml_buffer_idx - MIN_SPIKE_RECEPTOR ].add_value(
    e.get_rel_delivery_steps( nest::kernel().simulation_manager.get_slice_origin() ),
    weight * e.get_multiplicity() );
  B_.spike_input_received_[ nestml_buffer_idx - MIN_SPIKE_RECEPTOR ].add_value(
    e.get_rel_delivery_steps( nest::kernel().simulation_manager.get_slice_origin() ),
    1. );
}

void mat2_psc_exp_neuron_nestml::handle(nest::CurrentEvent& e)
{
#ifdef DEBUG
  std::cout << "[neuron " << this << "] mat2_psc_exp_neuron_nestml::handle(CurrentEvent)" << std::endl;
#endif
  assert(e.get_delay_steps() > 0);
  assert( e.get_rport() < B_.continuous_inputs_.size() );

  const double current = e.get_current();     // we assume that in NEST, this returns a current in pA
  const double weight = e.get_weight();

  B_.continuous_inputs_[e.get_rport()].add_value(
               e.get_rel_delivery_steps( nest::kernel().simulation_manager.get_slice_origin()),
               weight * current );
}

// -------------------------------------------------------------------------
//   Methods corresponding to event handlers
// -------------------------------------------------------------------------

