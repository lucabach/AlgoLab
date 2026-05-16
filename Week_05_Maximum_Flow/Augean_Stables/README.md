# Augean Stables

Given n stables with pollution constraints (each modeled as a linear inequality in terms of hours worked cleaning type A and type B channels), find the minimum total hours needed to make all stables clean.

## Approach

Binary search on total hours. For each candidate hour count, iterate over all splits (countA hours of type A, countB = total - countA of type B) and check feasibility using linear programming (CGAL QP solver). The LP checks whether the cumulative cleaning capacities from both channel types can simultaneously satisfy all stable constraints.
