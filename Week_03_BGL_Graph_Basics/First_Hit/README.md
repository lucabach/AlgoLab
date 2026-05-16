# First Hit

Given a ray and n line segments, find the first (closest) segment hit by the ray and output the exact intersection point.

## Approach

Use CGAL's exact constructions kernel. Shuffle segments to get expected O(n) performance. For each segment, skip it if it's farther than the current closest hit. On intersection, compute the exact intersection point (handling both point and segment overlap cases) and update the closest. Output the floored coordinates of the nearest intersection.
