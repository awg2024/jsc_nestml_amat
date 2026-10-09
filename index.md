# Benchmarking and Optimising Generated Neuron Models with NESTML

**Angus Gray**  
University of Edinburgh (`s2327079@ed.ac.uk`)  
Jülich Supercomputing Centre — Guest Student Programme 2026

## Abstract

Large-scale neuronal network simulations sit at the intersection of neuroscience, numerical modelling, and high-performance computing. At the modelling level, researchers describe neurons through membrane potentials, firing thresholds, synaptic currents, and systems of differential equations. At the implementation level, however, these models must ultimately be translated into efficient compiled code that can be executed for thousands or millions of neurons over many simulation time steps. NESTML bridges these two levels by providing a domain-specific language for describing neuron and synapse dynamics close to their mathematical formulation. This project, carried out during the Guest Student Programme at the Jülich Supercomputing Centre, evaluates this automated toolchain by implementing the augmented multi-timescale adaptive threshold (AMAT) model and benchmarking the generated code. Building on this, I also investigated how the computational cost of automatically generated solvers can be reduced by integrating selective common subexpression elimination (CSE) into the pipeline

## The NESTML Code-Generation Pipeline

While the NEST Simulator provides the core execution engine for large-scale spiking neural networks, NESTML serves as the domain-specific modeling layer for describing neuronal and synaptic dynamics. A NESTML specification defines state variables, parameters, differential equations, and event-driven updates in a high-level syntax, abstracting away low-level simulation C++ boilerplate (Linssen et al., 2025). During compilation, PyNESTML processes this model description through a sequence of intermediate transformations before invoking the target-specific C++ code generator. For models specified via ordinary differential equations (ODEs), PyNESTML delegates solver selection to ODE-toolbox. ODE-toolbox analyzes the system of equations and determines an optimal integration strategy. Analytically tractable systems are converted into exact matrix propagator expressions, whereas non-linear or coupled systems are routed to numerical solver interfaces (such as GSL). The resulting solver routines are then emitted directly into the C++ source code generated for NEST.

This automated pipeline decouples model design from computational implementation: researchers can modify mathematical formulations at the NESTML level, while solver construction and low-level code generation proceed automatically. Furthermore, performing optimizations at the symbolic solver stage allows performance enhancements to propagate across all generated neuron models automatically, eliminating the need for manual, model-specific C++ optimization (ODE-toolbox Documentation; Figure 1).

![High-level NESTML workflow for the NEST target](/Images/nestml-workflow.png)  
*Figure 1: High-level NESTML workflow for the NEST target, where neuron and synapse models are processed by PyNESTML to generate model code that is compiled by ODE-toolbox and executed by the NEST simulator engine (Linssen et al., 2025).*

## The AMAT Neuron Model

The Augmented Multi-Timescale Adaptive Threshold (AMAT) model is a point-neuron framework that combines leaky integrate-and-fire membrane dynamics with a dynamic, state-dependent firing threshold (Yamauchi et al., 2011). Upon emitting a spike, the threshold jumps instantaneously and subsequently relaxes toward its resting value across multiple distinct time constants. This multi-timescale structure allows the model to capture a wide repertoire of complex spiking behaviors—such as spike-frequency adaptation and variable firing patterns—while maintaining high predictive accuracy for spike timing at a low computational cost. Because its dynamics are governed by linear differential equations coupled with discrete spike-triggered jump conditions, the AMAT model maps cleanly onto the NESTML domain-specific language (DSL). Furthermore, NEST provides an established native C++ reference implementation, `amat2_psc_exp` (Heiberg et al., 2018), making the AMAT model an ideal test case for validating automated solver generation within the NESTML toolchain.

### Adaptive Threshold Dynamics

Mathematically, a spike is emitted at time $t$ whenever the membrane potential $V(t)$ reaches or exceeds the dynamic threshold $\theta(t)$:

$$V(t) \ge \theta(t)$$

where the total threshold $\theta(t)$ is decomposed into a constant baseline and three adaptive components:

$$\theta(t) = \omega + \theta_{\alpha_1}(t) + \theta_{\alpha_2}(t) + \theta_V(t)$$

Here, $\omega$ denotes the resting baseline threshold, while $\theta_{\alpha_1}(t)$ and $\theta_{\alpha_2}(t)$ represent fast and slow spike-triggered adaptation terms, respectively. The voltage-dependent term, $\theta_V(t)$, distinguishes the AMAT model from the classic Multi-Timescale Adaptive Threshold (MAT) formulation. By coupling the threshold directly to the recent trajectory of the membrane potential, $\theta_V(t)$ enables subthreshold sensitivity:

$$
theta_V(t) = \beta \int_0^\infty K(s) \frac{dV}{dt}(t-s) ds, \qquad K(s) = s e^{-s/\tau_V}
$$

Because all three adaptive components are linear filters driven by either discrete spike events or the membrane potential, each can be reformulated as a compact system of first-order linear ordinary differential equations (ODEs) with impulsive update rules. This mathematical linearity makes the AMAT model exceptionally well-suited for symbolic formulation in NESTML and exact propagator generation via ODE-toolbox.

### Integrator and Resonator Spiking Behavior

The voltage-dependent threshold term allows the adaptive threshold to evolve according to the recent trajectory of the membrane potential, in addition to spike-triggered adaptation. The strength and temporal profile of this interaction are governed by the coupling coefficient $\beta$ and the timescale $\gamma$ in $K(s)$, respectively. Varying these parameters determines whether the neuron operates primarily as an *integrator* (accumulating input monotonically) or as a *resonator* (exhibiting frequency-selective sensitivity). To isolate these dynamics, we applied a paired-pulse protocol consisting of a 1000 pA baseline stimulus at $t = 0\text{ ms}$ followed by a second identical stimulus after a variable inter-stimulus interval, $\Delta$, swept from 0 to 140 ms. We measured the maximum distance between the membrane potential and the threshold during the second stimulus; a smaller distance reflects heightened neuronal sensitivity to the second input.

With fixed $\gamma$ and increasing $\beta$ (values 0, 2, 4), we observed at $\beta = 0$, the voltage-dependent feedback vanishes, leaving only spike-triggered adaptation. Consequently, the threshold decays monotonically, and sensitivity is highest at short delays ($\Delta \to 0$), characteristic of an integrator. As $\beta$ increases (2, 4), the voltage-dependent feedback strengthens, introducing a non-monotonic sensitivity curve with a pronounced resonant peak at intermediate delays (Figure 2).

![Distance to threshold following a second stimulus](/Images/fixed_gamma.png)  
*Figure 2: Distance to threshold following a second 1000 pA stimulus as a function of the inter-stimulus delay $\Delta$, shown for increasing values of $\beta$ at fixed $\gamma = 1.5$.*

Conversely, varying $\gamma$ (values 0.5, 1.5, 3) while holding $\beta$ fixed modifies the decay rate of the voltage-dependent kernel (Figure 3). Larger values of $\gamma$ slow the $K(s)$ exponential decay, shifting the peak sensitivity toward longer delays, whereas smaller values compress the resonant window toward earlier times. Taken together these results display that both $\beta$ and $\gamma$ provide fine-grained control over the temporal tuning of the AMAT neuron.

![Distance to threshold for different values of gamma](/Images/fixed_beta.png)  
*Figure 3: Distance to threshold after a second 1000 pA stimulus as a function of the inter-stimulus delay $\Delta$, for different values of $\gamma$ with $\beta = 4.0$ fixed.*

### Validation against Native NEST

Before evaluating computational performance, we verified that the generated NESTML implementation faithfully reproduces the numerical dynamics of the reference native NEST AMAT model. Both implementations were simulated using identical parameter sets and subjected to a 1000 pA pulse protocol at $t = 10, 30, 210$, and $270\text{ ms}$, while recording the membrane potential ($V_m$) and total adaptive threshold ($\theta$) for direct comparison (Figure 4). The maximum absolute differences were $9.9 \times 10^{-14}\text{ mV}$ for $V_m$ (on the order of double-precision machine epsilon) and $2.2 \times 10^{-11}\text{ mV}$ for $\theta$, confirming that both models yield numerically equivalent state trajectories throughout the simulation. Establishing this precision baseline was an essential prerequisite prior to modifying the ODE-toolbox pipeline, guaranteeing that subsequent optimisations (such as Common Subexpression Elimination) preserve exact mathematical fidelity without introducing numerical drift.

![Comparison of native NEST and generated NESTML AMAT models](/Images/model_comparision.png)  
*Figure 4: Comparison of the native NEST and generated NESTML AMAT models.*

## Large-Scaling Network Benchmarking

To evaluate the generated AMAT model at scale, we used the Brunel balanced random network. The network consists of excitatory and inhibitory neuron populations, with four times as many excitatory as inhibitory neurons, connected randomly with a fixed connection probability. Each neuron receives external excitatory input in the form of independent Poisson spike trains. Inhibitory synapses are $g$ times stronger than excitatory ones, where $g$ sets the balance between excitation and inhibition. For sufficiently strong inhibition and moderate external drive, the network settles into an asynchronous irregular state (Figure 5). In this regime the excitatory and inhibitory inputs to each neuron largely cancel, so the membrane potential fluctuates around its mean and spikes are triggered by fluctuations rather than by a strong net drive. Individual neurons fire irregularly, and the population as a whole shows no global synchrony (Brunel, 2000). This network formulation creates a demanding, however, well-characterised benchmark. Its activity is dense and sustained, and its size can be scaled up by increasing the number of neurons.

![Brunel balanced neural network implementation](/Images/balanced_network.png)  
*Figure 5: Small Brunel balanced neural network implementation of the AMAT model (not used in benchmarking).*

### AMAT Benchmarking

To evaluate model performance in a realistic simulation context, we benchmarked the AMAT model within a Brunel balanced network architecture (Brunel, 2000). The network comprises $N = 12500$ neurons partitioned into $N_E = 10000$ excitatory and $N_I = 2500$ inhibitory subpopulations (a 4:1 ratio). Recurrent connectivity is established with a fixed probability of $\epsilon = 0.1$, resulting in $C_E = 1000$ excitatory and $C_I = 250$ inhibitory incoming connections per neuron. In total, the network contains approximately $1.56 \times 10^7$ recurrent synapses. We evaluated execution speed across both strong- and weak-scaling configurations on the JURECA supercomputing platform. In strong scaling, the total network size remains fixed while node count increases; ideal scaling yields an inverse-proportional decrease in wall-clock time. In weak scaling, the network size scales proportionally with available compute nodes, maintaining a constant workload per node such that ideal scaling results in flat execution times. NEST parallelizes simulations using MPI, distributing neurons across processes in a round-robin scheme. Each process updates its assigned subset of neurons and manages their incoming synaptic targets. Simulation runtime is dominated by two primary operations: updating local neuronal state variables at each integration step and delivering spikes across MPI processes once per minimum synaptic delay. 

Benchmarks were executed across 2, 4, and 8 compute nodes, with five independent repetitions per configuration. We compared the unoptimized NESTML model against its CSE-optimized variant and the hand-crafted, native NEST implementation (Figure 6). Across all node configurations, the baseline NESTML implementation exhibited an approximate 1.38x wall-clock overhead compared to native NEST. In profiling, NESTML models exhibited a 19.2% L1 load and 7.85% greater CPU cycles, with -4.23% instructions per cycle. This memory and cycle change is expected with native C++ NEST models utilising highly compact, hand-tuned data structures. In contrast, NESTML generates additional abstraction and generalized C++ wrappers to support modularity, interface flexible solvers, and manage state variables, incurring structural compute and memory overheads.

![AMAT performance benchmark](/Images/amat_benchmark.png)  
*Figure 6: AMAT performance benchmark across strong and weak scaling experiments.*

## ODE-toolbox and Common Subexpression Elimination

As introduced previously, NESTML uses ODE-toolbox within its code-generation pipeline (Figure 1) to select and generate numerical solvers for systems of differential equations. However, automatically generated C++ solver expressions often lack the optimisations present in NEST's hand-crafted C++ implementations, contributing to an observed 1.32x performance gap. A source of overhead in ODE-toolbox is the generation of repeated symbolic subexpressions. These redundancies present a key target for optimization via **Common Subexpression Elimination (CSE)** (Meurer et al., 2017). CSE identifies duplicate expressions within a system of equations, computes them once, and stores the result in a temporary variable for reuse.

Consider a set of simplified propagator equations:

$$P_x = \exp\left(-\frac{h}{\tau}\right)$$

$$P_y = \exp\left(-\frac{h}{\tau}\right)$$

$$P_z = 1 - \exp\left(-\frac{h}{\tau}\right)$$

Without optimization, the computationally expensive transcendental term $\exp(-h/\tau)$ is evaluated three times per update step. Applying CSE transforms the system into:

$$\text{tmp}_0 = \exp\left(-\frac{h}{\tau}\right)$$

$$P_x = \text{tmp}_0$$

$$P_y = \text{tmp}_0$$

$$P_z = 1 - \text{tmp}_0$$

While mathematically identical, this substitution replaces two transcendental function calls and two divisions with fast register reads. In spiking neural network simulations, where neuron update functions execute across millions of integration steps (e.g., 100,000 steps for a 1000 ms simulation at $h = 0.01\text{ ms}$), eliminating redundant arithmetic per step yields substantial performance gains over the course of a simulation.

### Weighted-CSE Profitability Analysis

Applying CSE indiscriminately across all redundant subexpressions is not inherently advantageous. While replacing a repeated expression with a temporary variable eliminates recomputation, the temporary variable itself incurs a memory overhead, where it must be allocated, written to, and stored to a register. For complex, computationally heavy operations that are reused frequently, this trade-off is highly favorable. However, for inexpensive operations repeated only a few times, introducing a temporary variable yields minimal performance gains or can even introduce slowdowns due to increased register spillover. 

We therefore assign heuristic costs that reflect the relative expense of arithmetic and transcendental operations rather than attempting to model exact CPU-cycle counts ($C_{\text{expr}}$). This cost reflects the underlying hardware instruction complexity, where high-cost operations (e.g., $\sin$, $\cos$, $\exp$, $\ln$) and general exponentiation (`pow`) cannot be executed in a single CPU cycle. Instead, they require multi-cycle microcoded sequences, specialized vector units, or calls to standard C library routines (`libm`), consuming tens to hundreds of clock cycles. Whereas, basic arithmetic operations, such as addition, subtraction, and multiplication, are handled directly by single-cycle Arithmetic Logic Units (ALUs) or fused multiply-add (FMA) pipelines, executing with minimal latency. For a candidate subexpression with estimated evaluation cost $C_{\text{expr}}$ that appears $N_{\text{uses}}$ times, the net estimated benefit $B$ is defined as:

$$B = (N_{\text{uses}} - 1) C_{\text{expr}} - C_{\text{tmp}}$$

where $C_{\text{tmp}}$ denotes the estimated temporary overhead cost associated with initialising and accessing the temporary variable. The multiplier $(N_{\text{uses}} - 1)$ isolates the number of redundant evaluations avoided. To ensure that subexpression elimination is applied selectively, a candidate transformation is retained if and only if it satisfies the threshold condition:

$$B \ge B_{\min}$$

In the current ODE-toolbox implementation, the temporary variable overhead is assigned a unit weight of $C_{\text{tmp}} = 1$, and the minimum acceptable benefit threshold is set to $B_{\min} = 3$. By enforcing this threshold, CSE operates as a cost-aware optimization pass: expensive mathematical expressions repeated across the solver's differential equations are aggressively factored out, whereas lightweight or infrequently repeated operations are left inline to avoid unnecessary temporary variable allocations.

### AMAT CSE Benchmarking

The initial performance evaluation of the weighted CSE implementation utilised the AMAT neuron model. As the AMAT model is analytically solvable, its state variables can be transformed explicitly into an exact propagator matrix that advances the system state across discrete simulation timesteps. Consequently, model updates are inherently computationally lightweight, requiring minimal runtime arithmetic. 

During benchmark tests, enabling weighted CSE yielded only modest wall-clock performance improvements, achieving a 1.01x speedup under strong-scaling conditions and a 1.03x speedup under weak-scaling conditions relative to the NESTML baseline. Rather than indicating a flaw in the optimization pass, this outcome demonstrates that analytically solved models like AMAT present a sparse search space for subexpression elimination. The symbolic derivation step inherently collapses the model dynamics into a compact algebraic update, leaving very few repeated or expensive expressions for CSE to remove. 

In profiling, total CPU cycle counts remained virtually unchanged at a +0.01% variation, while total executed instructions shifted by a negligible -0.002%. Memory access overhead and execution efficiency exhibited similarly minor adjustments, with L1 data cache loads decreasing by 0.49% and instructions per cycle dropping by 0.45%. These profiling metrics confirm that the baseline code generator already produces a near-optimal instruction sequence for analytically derived propagators, with the potential for performance via reducing symbolic expression constrained by the low cost of the propagator equations.

![AMAT CSE performance benchmark](/Images/amat_cse_benchmark.png)  
*Figure 7: Performance benchmark evaluation showcasing execution scaling metrics.*

### Hodgkin–Huxley CSE Benchmarking

To evaluate the optimization under a more computationally demanding workload, we extended our benchmarking to a Hodgkin–Huxley neuron model (Hodgkin & Huxley, 1952). Unlike analytically solved model architectures, the Hodgkin–Huxley model describes the nonlinear ionic dynamics of $\text{Na}^+$ and $\text{K}^+$ channels via a coupled system of nonlinear ordinary differential equations. Because an analytical solution is unavailable, the state updates require iterative numerical integration. In NESTML, complex systems of differential equations are solved using the Runge–Kutta–Fehlberg method (RK45) provided by the GNU Scientific Library (GSL). Within each simulation timestep, the GSL solver evaluates the model's derivative functions multiple times (sub-stepping) to approximate the updated state variables accurately. As a result, substantially more arithmetic is performed during every neuronal update step compared to exact integration schemes. This operational distinction makes numerical solvers, with Hodgkin–Huxley representing our most computationally expensive model, an ideal test case for CSE. 

During benchmark experiments, CSE achieved a 14.7% reduction in total executed CPU cycles alongside a 10.9% drop in total instruction count. Memory access overhead saw a corresponding decrease, with L1 data cache loads falling by 10.2%. Interestingly, instructions per cycle improved by 4.1%, indicating that in addition to executing fewer total instructions, execution efficiency improved. Together, these reductions yielded a 1.17x wall-clock speedup for NESTML+CSE relative to baseline NESTML (Figure 8). Taken together, these metrics confirm that the primary performance benefit stems directly from eliminating redundant arithmetic work and reducing memory load operations.

![Hodgkin-Huxley performance benchmark](/Images/hh_performance_benchmark.png)  
*Figure 8: Hodgkin-Huxley performance benchmark across strong and weak scaling experiments.*

## Discussion and Future Work

We have demonstrated that the AMAT model can be expressed natively in NESTML while matching the numerical precision of NEST's hand-tuned C++ implementation. To support community adoption for the AMAT model, we have provided an open-source Jupyter notebook tutorial guiding neuroscientists through the usage, configuration, and simulation of this model (`doc/tutorials/amat_model/nestml_amat_neuron_tutorial.ipynb` on NESTML repository)

Our results justify making CSE a selective, cost-aware optimization pass. For analytically-solvable models like AMAT, CSE yields marginal speedups because the exact propagator equations are already mathematically compact. Conversely, for numerically integrated systems like Hodgkin–Huxley, where ODE solvers perform repeated sub-step evaluations, eliminating redundant arithmetic yields substantial speedups across CPU cycles, instruction counts, and memory loads. The performance gain of symbolic CSE scales directly with the operational density of the model's differential equations. These optimisations will be merged onto ODE-toolbox to enable all end-users to benefit from these optimisation gains when compiling their custom NESTML model (`odetoolbox/expression_optimisation.py` on ODE-toolbox repository). 

Future research could focus on extending the symbolic optimization beyond single-compartment point neurons to multi-compartment architectures and complex synaptic plasticity rules, where high-dimensional state updates present an even greater region for symbolic arithmetic reduction.

## Acknowledgments

I would like to thank my supervisor Charl Linssen for his guidance and support throughout the programme, and to Ivo Kabadshow for organising the Guest Student Programme.

## References 

Brunel, N. (2000) 'Dynamics of sparsely connected networks of excitatory and inhibitory spiking neurons', Journal of Computational Neuroscience, 8(3), pp. 183–208. doi: 10.1023/A:1008925309027.

Gewaltig, M.-O. and Diesmann, M. (2007) 'NEST (NEural Simulation Tool)', Scholarpedia, 2(4), p. 1430. doi: 10.4249/scholarpedia.1430.

Heiberg, T., Kriener, B., Tetzlaff, T., Einevoll, G.T. and Plesser, H.E. (2018) 'Firing-rate models for neurons with a broad repertoire of spiking behaviors', Journal of Computational Neuroscience, 45(2), pp. 103–132.

Hodgkin, A.L. and Huxley, A.F. (1952) 'A quantitative description of membrane current and its application to conduction and excitation in nerve', The Journal of Physiology, 117(4), pp. 500–544. doi: 10.1113/jphysiol.1952.sp004764.

Izhikevich, E.M. (2003) 'Simple model of spiking neurons', IEEE Transactions on Neural Networks, 14(6), pp. 1569–1572.

Kobayashi, R., Tsubo, Y. and Shinomoto, S. (2009) 'Made-to-order spiking neuron model equipped with a multi-timescale adaptive threshold', Frontiers in Computational Neuroscience, 3, p. 762.

Linssen, C., Babu, P.N., Eppler, J.M., Koll, L., Rumpe, B. and Morrison, A. (2025) 'NESTML: a generic modeling language and code generation tool for the simulation of spiking neural networks with advanced plasticity rules', Frontiers in Neuroinformatics, 19, p. 1544143.

Meurer, A., Smith, C.P., Paprocki, M., Čertík, O., Kirpichev, S.B., Rocklin, M., Kumar, A., Ivanov, S., Moore, J.K., Roučka, Š., Saboo, A., Fernando, I., Kulal, S., Cimrman, R. and Scopatz, A. (2017) 'SymPy: symbolic computing in Python', PeerJ Computer Science, 3, p. e103. doi: 10.7717/peerj-cs.103.

NEST Initiative (2025) NESTML: A domain specific language for neuron and synapse models in spiking neural network simulation. Available at: https://github.com/nest/nestml (Accessed: October 2026).

NEST Initiative (2025) ODE-toolbox Documentation. Available at: https://ode-toolbox.readthedocs.io/ (Accessed: October 2026).

NEST Initiative (2025) ODE-toolbox: Automatic selection and generation of integration schemes for systems of ordinary differential equations. Available at: https://github.com/nest/ode-toolbox (Accessed: October 2026).

NEST Initiative (2026) NESTML: Neuron Modeling Language for NEST. Available at: https://github.com/nest/nestml (Accessed: October 2026).

NEST Initiative (2026) ODE-toolbox Documentation. Available at: https://ode-toolbox.readthedocs.io/en/main/ (Accessed: October 2026).

NEST Initiative (2026) ODE-toolbox: Choose and generate solvers for systems of ordinary differential equations. Available at: https://github.com/nest/ode-toolbox (Accessed: October 2026).

SymPy Development Team (2026) SymPy Documentation: Rewriting and Common Subexpression Elimination. Available at: https://docs.sympy.org/latest/modules/rewriting.html (Accessed: October 2026).

Yamauchi, S., Kim, H. and Shinomoto, S. (2011) 'Elemental spiking neuron model for reproducing diverse firing patterns and predicting precise firing times', Frontiers in Computational Neuroscience, 5, p. 42.








