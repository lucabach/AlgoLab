# Antenna

Given n points, find the radius of the smallest enclosing circle (rounded up to the nearest integer).

## Approach

Use CGAL's `Min_circle_2` with randomized incremental construction to find the minimum enclosing circle in expected O(n) time. Extract the support points, reconstruct the exact circle using the sqrt kernel, compute the exact radius, and round up.
