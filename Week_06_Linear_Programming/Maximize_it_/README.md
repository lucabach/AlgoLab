# Maximize It!

A demo problem for CGAL's linear programming solver with two variants of small LP instances.

## Approach

Directly encode two small LPs using CGAL's `Quadratic_program` API. Program 1 minimizes `ax - by` subject to a few constraints with non-negative variables. Program 2 has no lower bounds and uses a third variable. Solve with `CGAL::solve_linear_program` and output the rounded objective value, or "no"/"unbounded" as appropriate.
