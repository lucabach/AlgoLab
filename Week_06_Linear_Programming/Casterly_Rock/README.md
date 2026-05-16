# Casterly Rock

Given n noble houses and m common houses, find a sewage line separating nobles (left) from commoners (right) satisfying a budget constraint, then find a perpendicular fresh-water canal minimizing its maximum distance to all houses.

## Approach

Use two LP solves. First, fix the sewage line slope (a=1) and find coefficients b, c such that all nobles satisfy ax+by+c <= 0 and all commoners satisfy ax+by+c >= 0; check feasibility with and without the budget constraint to output "Y" or "B". Then add the perpendicular water line (b_water = 1, b_sewer = -a_water) and introduce a variable d for the maximum distance to all houses, minimizing d using CGAL's LP solver.
