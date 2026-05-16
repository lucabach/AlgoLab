# Inball

Given n half-planes in d dimensions (each defined by a linear inequality), find the radius of the largest ball that fits inside all of them.

## Approach

Formulate as an LP: variables are the ball center coordinates plus the radius r. For each half-plane `a·x <= b`, add the constraint `a·x + ||a|| * r <= b`. Maximize r (equivalently minimize -r). Use CGAL's LP solver with exact arithmetic and output the result.
