# Bistro

Given a set of existing restaurant locations and a set of candidate new locations, find the squared distance from each candidate to its nearest existing restaurant.

## Approach

Build a Delaunay triangulation over the existing restaurant points. For each new location, use `nearest_vertex` to find the closest existing point in O(log n), then output the squared distance.
