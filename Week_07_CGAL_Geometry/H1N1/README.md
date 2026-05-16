# H1N1

Given infected person locations and query people with a required escape gap, determine whether each query person can flee to infinity without coming within distance d of any infected person.

## Approach

- Build a Delaunay triangulation over the infected locations and annotate each triangular face with the maximum "escape diameter" reachable from infinity, propagated inward via a max-priority-queue flood fill from infinite faces.
- For a query point, first check if it is already too close to the nearest infected person (distance < d); if so, output "n".
- If the face containing the query point is infinite, output "y". Otherwise, check whether the face's stored escape diameter is at least 4d (so a circle of diameter 2d can pass through).
