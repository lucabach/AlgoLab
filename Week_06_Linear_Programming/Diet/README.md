# Diet

Given m foods and n nutrients, find the minimum-cost diet (non-negative quantities of each food) such that each nutrient stays within a given [min, max] range.

## Approach

Formulate as an LP: variables are food quantities (lower bound 0), with two constraints per nutrient (upper and lower bound). Set objective as total cost. Solve with CGAL's LP solver; output the floored minimum cost or "No such diet." if infeasible.
