# Legions

Given a starting position and n advancing enemy lines (each a half-plane moving at some speed), find the maximum time you can survive before being caught.

## Approach

- Formulate as a linear program: maximize the survival time D, subject to each legion's constraint that the query point plus D times the line's advance rate stays on the correct side of the line.
- Flip the half-plane orientation based on which side the starting point is on, then solve with CGAL's LP solver.
