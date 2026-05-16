# Hiking Maps

A hiking route has m waypoints (m-1 legs). There are n triangular map pieces; find the minimum number of consecutive maps needed to cover every leg of the route.

## Approach

Precompute for each map i and each leg j whether the leg is fully contained in the triangle (both endpoints on the non-negative side of all three oriented half-planes). Then use a sliding window over maps: expand the right end until all legs are covered, then shrink the left end as far as possible while still covered. Track the minimum window size.
