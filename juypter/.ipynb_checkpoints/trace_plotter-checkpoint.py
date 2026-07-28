from __future__ import annotations

from dataclasses import dataclass
from typing import Mapping, Sequence, Literal

import numpy as np
import matplotlib.pyplot as plt


ModelKind = Literal["nest", "nestml"]


@dataclass
class TraceSpec:
    key: str
    label: str
    ylabel: str | None = None
    fill_to_zero: bool = False
    show_zero: bool = False
    lw: float = 1.3


@dataclass
class PlotBundle:
    name: str
    time: np.ndarray
    traces: dict[str, np.ndarray]
    input_times: Sequence[float] = ()
    spike_times: Sequence[float] = ()


def _get_array(events: Mapping, key: str, fallback: np.ndarray | None = None) -> np.ndarray:
    if key in events:
        return np.asarray(events[key])
    if fallback is not None:
        return np.asarray(fallback)
    raise KeyError(f"Missing key '{key}' in events dictionary.")


def _reconstruct_spike_kernel(time, spike_times, amplitude, tau):
    """
    Reconstruct spike-history threshold component:

        sum_k amplitude * exp(-(t - t_k) / tau), for t >= t_k

    This is useful for native NEST AMAT, which records total V_th but
    may not expose V_th_alpha_1 and V_th_alpha_2 separately.
    """
    time = np.asarray(time)
    kernel = np.zeros_like(time, dtype=float)

    if spike_times is None:
        return kernel

    for tk in spike_times:
        mask = time >= tk
        kernel[mask] += amplitude * np.exp(-(time[mask] - tk) / tau)

    return kernel


def standardise_amat_events(
    events: Mapping,
    *,
    model_kind: ModelKind,
    omega: float,
    E_L: float = -70.0,
    name: str,
    input_times: Sequence[float] = (),
    spike_events: Mapping | None = None,
    params: Mapping | None = None,
) -> PlotBundle:
    """
    Convert native NEST or NESTML AMAT events into common plotting variables.

    Returned traces:
        V_m
        theta
        theta_relative
        distance
        V_th_alpha_1
        V_th_alpha_2
        V_th_v
        V_th_v_aux
        input_proxy

    Native NEST:
        Uses recorded V_th as the relative total threshold.
        Absolute threshold is E_L + V_th.

    NESTML:
        Reconstructs relative threshold as:
        omega + V_th_alpha_1 + V_th_alpha_2 + V_th_v

        Absolute threshold is:
        E_L + omega + V_th_alpha_1 + V_th_alpha_2 + V_th_v
    """

    time = _get_array(events, "times")
    V_m = _get_array(events, "V_m")
    zeros = np.zeros_like(V_m)

    if spike_events is not None and "times" in spike_events:
        spike_times = np.asarray(spike_events["times"])
    else:
        spike_times = np.array([])

    params = params or {}

    alpha_1 = params.get("alpha_1", 0.0)
    alpha_2 = params.get("alpha_2", 0.0)
    tau_1 = params.get("tau_1", params.get("tau_1", 10.0))
    tau_2 = params.get("tau_2", params.get("tau_2", 200.0))

    if model_kind == "nest":
        raw_V_th = _get_array(events, "V_th")
        V_th_v = _get_array(events, "V_th_v", zeros)

        # Native NEST records V_th as a relative threshold, usually around omega.
        theta_relative = raw_V_th
        theta = E_L + theta_relative

        # Native NEST does not expose alpha components separately.
        # Reconstruct them from output spikes and known parameters.
        V_th_alpha_1 = _reconstruct_spike_kernel(
            time=time,
            spike_times=spike_times,
            amplitude=alpha_1,
            tau=tau_1,
        )

        V_th_alpha_2 = _reconstruct_spike_kernel(
            time=time,
            spike_times=spike_times,
            amplitude=alpha_2,
            tau=tau_2,
        )

        V_th_v_aux = zeros
        input_proxy = _get_array(events, "I_syn_ex", zeros)

    elif model_kind == "nestml":
        V_th_alpha_1 = _get_array(events, "V_th_alpha_1", zeros)
        V_th_alpha_2 = _get_array(events, "V_th_alpha_2", zeros)
        V_th_v = _get_array(events, "V_th_v", zeros)
        V_th_v_aux = _get_array(events, "V_th_v_aux", zeros)

        theta_relative = omega + V_th_alpha_1 + V_th_alpha_2 + V_th_v
        theta = E_L + theta_relative

        input_proxy = zeros

    else:
        raise ValueError("model_kind must be 'nest' or 'nestml'.")

    distance = V_m - theta

    return PlotBundle(
        name=name,
        time=time,
        traces={
            "V_m": V_m,
            "theta": theta,
            "theta_relative": theta_relative,
            "distance": distance,
            "V_th_alpha_1": V_th_alpha_1,
            "V_th_alpha_2": V_th_alpha_2,
            "V_th_v": V_th_v,
            "V_th_v_aux": V_th_v_aux,
            "input_proxy": input_proxy,
        },
        input_times=input_times,
        spike_times=spike_times,
    )



class TracePlotter:
    def __init__(
        self,
        trace_specs: Sequence[TraceSpec],
        *,
        time_unit: str = "ms",
    ):
        self.trace_specs = list(trace_specs)
        self.time_unit = time_unit

    @staticmethod
    def _nice_ylim(y: np.ndarray, pad_fraction: float = 0.08) -> tuple[float, float]:
        y = np.asarray(y)
        y = y[np.isfinite(y)]

        if y.size == 0:
            return -1.0, 1.0

        ymin = float(np.min(y))
        ymax = float(np.max(y))

        if np.isclose(ymin, ymax):
            centre = ymin
            spread = max(abs(centre) * 0.05, 1.0)
            return centre - spread, centre + spread

        spread = ymax - ymin
        pad = spread * pad_fraction
        return ymin - pad, ymax + pad

    def plot_side_by_side(
        self,
        bundles: Sequence[PlotBundle],
        *,
        title: str | None = None,
        figsize: tuple[float, float] | None = None,
        xlim: tuple[float, float] | None = None,
        align_y_by_row: bool = False,
        row_gap: float = 0.18,
        column_gap: float = 0.12,
    ):
        bundles = list(bundles)
        n_rows = len(self.trace_specs)
        n_cols = len(bundles)

        if n_rows == 0:
            raise ValueError("No trace specs provided.")
        if n_cols == 0:
            raise ValueError("No bundles provided.")

        figsize = figsize or (5.4 * n_cols, 1.7 * n_rows)

        fig, axes = plt.subplots(
            n_rows,
            n_cols,
            sharex="col",
            squeeze=False,
            figsize=figsize,
            gridspec_kw={"hspace": row_gap, "wspace": column_gap},
        )

        row_ylims = {}
        if align_y_by_row:
            for spec in self.trace_specs:
                combined = np.concatenate([b.traces[spec.key] for b in bundles])
                row_ylims[spec.key] = self._nice_ylim(combined)

        for col_idx, bundle in enumerate(bundles):
            for row_idx, spec in enumerate(self.trace_specs):
                ax = axes[row_idx, col_idx]

                t = bundle.time
                y = bundle.traces[spec.key]

                ax.plot(t, y, lw=spec.lw)

                if spec.fill_to_zero:
                    ax.fill_between(t, 0, y, alpha=0.16)

                if spec.show_zero:
                    ax.axhline(0, linestyle=":", lw=1.0, alpha=0.8)

                for pt in bundle.input_times:
                    ax.axvline(pt, linestyle="--", lw=0.9, alpha=0.35)

                if row_idx == 0:
                    for st in bundle.spike_times:
                        ax.annotate(
                            "",
                            xy=(st, 1.0),
                            xycoords=("data", "axes fraction"),
                            xytext=(st, 1.13),
                            textcoords=("data", "axes fraction"),
                            arrowprops=dict(arrowstyle="-", lw=1.4),
                            clip_on=False,
                        )

                if xlim is not None:
                    ax.set_xlim(*xlim)

                if align_y_by_row:
                    ax.set_ylim(*row_ylims[spec.key])
                else:
                    ax.set_ylim(*self._nice_ylim(y))

                if col_idx == 0:
                    ax.set_ylabel(spec.ylabel or spec.label)

                if row_idx == 0:
                    ax.set_title(bundle.name, fontsize=12)

                if row_idx == n_rows - 1:
                    ax.set_xlabel(f"Time ({self.time_unit})")
                else:
                    ax.tick_params(labelbottom=False)

                ax.text(
                    0.02,
                    0.84,
                    spec.label,
                    transform=ax.transAxes,
                    fontsize=10,
                    va="top",
                    ha="left",
                    bbox=dict(facecolor="white", alpha=0.65, edgecolor="none", pad=2),
                )

                for spine in ["top", "right"]:
                    ax.spines[spine].set_visible(False)

                ax.grid(True, linestyle=":", alpha=0.35)

        if title:
            fig.suptitle(title, y=1.01, fontsize=14)

        fig.tight_layout()
        return fig, axes