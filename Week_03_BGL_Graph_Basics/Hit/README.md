# Hit

Given a ray and n line segments, determine whether the ray intersects any of them.

## Approach

Use CGAL's `do_intersect` with an exact predicates kernel to test the ray against each segment in order. Print "yes" on the first intersection found, "no" if none.
