from __future__ import annotations
from dataclasses import dataclass, field
import numpy as np
import matplotlib.pyplot as plt


@dataclass
class _Trace:
    name: str
    y: np.ndarray
    color: str = "black"
    label: str | None = None
    label_color: str | None = None
    lw: float = 1.4
    fill: bool = False
    height_ratio: float = 1.0


class TracePlotter:
   
   # Stack an arbitrary number of time-aligned traces on shared time axis,
   # in the minimal-axis "textbook figure" style: no box, no ticks, just
   # colored trace labels and an optional scale bar.
    

    def __init__(self, time: np.ndarray, time_unit: str = "ms"):
        self.time = np.asarray(time)
        self.time_unit = time_unit
        self.traces: list[_Trace] = []
        self.spike_times: list[float] = []

    # building the figure content
    def add_trace(
        self,
        name: str,
        y: np.ndarray,
        color: str = "black",
        label: str | None = None,
        label_color: str | None = None,
        lw: float = 1.4,
        fill: bool = False,
        height_ratio: float = 1.0,
    ) -> "TracePlotter":
        #Add one time series to be plotted as its own stacked row."""
        y = np.asarray(y)
        if y.shape != self.time.shape:
            raise ValueError(
                f"Trace '{name}' has shape {y.shape}, expected {self.time.shape} "
                f"to match the time array."
            )
        self.traces.append(
            _Trace(
                name=name,
                y=y,
                color=color,
                label=label if label is not None else name,
                label_color=label_color or color,
                lw=lw,
                fill=fill,
                height_ratio=height_ratio,
            )
        )
        return self

    def add_spike(self, spike_time: float) -> "TracePlotter":
        #Mark a vertical spike line spanning every row, at a given time."""
        self.spike_times.append(spike_time)
        return self

    # ---- rendering --------------------------------------------------------

    def plot(
        self,
        figsize: tuple[float, float] | None = None,
        scalebar_ms: float | None = 20,
        title: str | None = None,
        row_gap: float = 0.0,
    ):
        """
        Render the stacked figure.

        Returns (fig, axes) so the caller can further customize or save it.
        """
        n = len(self.traces)
        if n == 0:
            raise ValueError("No traces added yet — call add_trace() first.")

        heights = [t.height_ratio for t in self.traces]
        figsize = figsize or (6, 1.1 * n)

        fig, axes = plt.subplots(
            n,
            1,
            sharex=True,
            figsize=figsize,
            gridspec_kw={"height_ratios": heights, "hspace": row_gap},
        )
        if n == 1:
            axes = [axes]

        for ax, tr in zip(axes, self.traces):
            ax.plot(self.time, tr.y, color=tr.color, lw=tr.lw)
            if tr.fill:
                ax.fill_between(self.time, tr.y, color=tr.color, alpha=0.15)

            # minimal-axis "textbook" look: no box, no ticks
            for spine in ax.spines.values():
                spine.set_visible(False)
            ax.set_xticks([])
            ax.set_yticks([])
            ax.set_facecolor("none")

            # colored inline label instead of a legend
            if tr.label:
                ax.text(
                    0.02,
                    0.82,
                    tr.label,
                    transform=ax.transAxes,
                    color=tr.label_color,
                    fontsize=11,
                    va="top",
                    ha="left",
                )

            # spike marker(s) drawn on every row so, with hspace=0, they
            # appear as one continuous vertical line through the stack
            
            for st in self.spike_times:
                axes[0].annotate(
                    "",
                    xy=(st, 1.0),
                    xycoords=("data", "axes fraction"),
                    xytext=(st, 1.15),
                    textcoords=("data", "axes fraction"),
                    arrowprops=dict(arrowstyle="-", color="black", lw=1.5),
                )

        if title:
            fig.suptitle(title, y=1.02)

        if scalebar_ms is not None:
            self._draw_scalebar(axes[-1], scalebar_ms)

        fig.tight_layout()
        return fig, axes

    def _draw_scalebar(self, ax, length: float):
        """Draw a small horizontal time scale bar under the bottom-most axis."""
        xlim = ax.get_xlim()
        ylim = ax.get_ylim()
        x0 = xlim[1] - length - 0.05 * (xlim[1] - xlim[0])
        y0 = ylim[0] - 0.15 * (ylim[1] - ylim[0])
        ax.plot([x0, x0 + length], [y0, y0], color="black", lw=2, clip_on=False)
        ax.text(
            x0 + length / 2,
            y0 - 0.12 * (ylim[1] - ylim[0]),
            f"{length:g} {self.time_unit}",
            ha="center",
            va="top",
            fontsize=9,
            clip_on=False,
        )