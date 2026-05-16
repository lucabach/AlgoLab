# Attack of the Clones

Jedi knights each guard a circular arc of a ring with n sectors. Find the maximum number of non-overlapping arcs that can be simultaneously selected.

## Approach

Find the sector covered by the fewest Jedi (minimum overlap). For each Jedi whose arc ends in that sector, try starting a greedy interval scheduling sweep from just after their arc ends, shifting the circular ring so that point becomes position 0. Pick greedily: always choose the Jedi whose arc ends earliest and starts after the current position. Take the maximum count across all starting positions tried.
