


from __future__ import annotations
from dataclasses import dataclass, field
import numpy as np
import matplotlib.pyplot as plt

@dataclass
class _Trace:
    """ 
    Container storing all information needed to draw one trace.
    Each instance represents one row in the stacked figure, including 
    the data values, appearance, and optional label. 
    """
    name: str # Internal identifier
    y: np.ndarray # Signal values
    color: str = "black" # Line colour
    label: str | None = None # Displayed label
    label_color: str | None = None 
    lw: float = 1.4 # Line width
    fill: bool = False # Whether to shade beneath the trace
    height_ratio: float = 1.0 # Relative subplot height


class TracePlotter:
    """ 
    Utility class for producing vertically stacked traces sharing 
    a common time axis. 
    """

    # Store the common time vector used by every trace.
    # All signals added to the plot must have this same length.
    def __init__(self, time: np.ndarray, time_unit: str = "ms"):
        self.time = np.asarray(time)
        self.time_unit = time_unit
        self.traces: list[_Trace] = [] # List storing every trace to be plotted.
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
        # Register a new signal for plotting.
        # Each added trace occupies one subplot in the final stacked figure.
        y = np.asarray(y)
        if y.shape != self.time.shape:
            # Ensure every signal is sampled on the same time grid.
            raise ValueError(
                f"Trace '{name}' has shape {y.shape}, expected {self.time.shape} "
                f"to match the time array."
            )
        self.traces.append(
            # Package all plotting options into a _Trace object so that rendering can done later
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
        return self # Return the object itself to allow method chaining, easier when call

    def add_spike(self, spike_time: float) -> "TracePlotter": #Mark a vertical spike line spanning every row
        self.spike_times.append(spike_time)
        return self

    # render plot 
    def plot(
        self,
        figsize: tuple[float, float] | None = None,
        scalebar_ms: float | None = 20,
        title: str | None = None,
        row_gap: float = 0.0,
    ):
        """
        Render all stored traces as vertically stacked subplots sharing
        a common time axis.

        Returns (fig, axes) matplotlib figure and axes objects 
        """
        n = len(self.traces) # Number of stacked rows required.
        if n == 0:
            raise ValueError("No traces added yet — call add_trace() first.")

        heights = [t.height_ratio for t in self.traces] # Allow selected traces to occupy more space 
        figsize = figsize or (6, 1.1 * n)

        fig, axes = plt.subplots( # Create one subplot per trace with a shared horizontal time axis.
            n,
            1,
            sharex=True,
            figsize=figsize,
            gridspec_kw={"height_ratios": heights, "hspace": row_gap},
        )
        if n == 1: # plt.subplots returns a single Axes rather than a list when n=1, wrap it in list so there's no mismatch 
            axes = [axes]

        for ax, tr in zip(axes, self.traces): # Draw each stored trace onto its corresponding subplot.
            ax.plot(self.time, tr.y, color=tr.color, lw=tr.lw)
            if tr.fill: # Optional shaded region beneath the trace for emphasis.
                ax.fill_between(self.time, tr.y, color=tr.color, alpha=0.15)

            # Remove all axis decorations so that attention is focused on waveform itself. 
            # Displayed in the Yamouchi et al., 2011 & Heiberg et al., 2018 papers. 
            for spine in ax.spines.values():
                spine.set_visible(False)
            ax.set_xticks([])
            ax.set_yticks([])
            ax.set_facecolor("none")

            # Placing a coloured label directly inside the subplot.
            # This avoids the need for a separate legend.
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

            # Draw spike markers above the uppermost trace.
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
            fig.suptitle(title, y=1.02) # Optional figure title.

        if scalebar_ms is not None:
            self._draw_scalebar(axes[-1], scalebar_ms) # Replace conventional x-axis ticks with a simple horizontal
                                                    # scale bar indicating elapsed simulation time.

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