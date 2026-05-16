# The Empire Strikes Back

Given asteroids with densities, shot positions, and hunter positions that block shots, determine whether it is feasible to destroy all asteroids using a limited total energy budget.

## Approach

- Build a Delaunay triangulation of hunters to efficiently find, for each shot, the maximum radius it can reach before being blocked.
- Set up a linear program: each shot's energy variable must together provide at least the required density to each reachable asteroid (weighted by inverse squared distance), subject to a total energy cap.
- Solve with CGAL's LP solver and output feasibility.
