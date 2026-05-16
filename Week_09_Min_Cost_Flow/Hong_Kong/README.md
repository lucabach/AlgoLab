# Hong Kong

Given trees forming obstacles and balloons of radius s, determine whether each balloon can escape to infinity without being punctured by any tree of radius r.

## Approach

- Build a Delaunay triangulation of the trees and annotate each face with the maximum squared circumradius reachable from infinity, propagated via a priority-queue flood fill (similar to H1N1 but using circumradius instead of edge length).
- For each balloon, check if it starts too close to a tree (distance < r+s). If its containing face is infinite it can trivially escape; otherwise compare the face's stored path clearance against the required diameter 2(r+s).
