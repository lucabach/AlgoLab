# Germs

Given n bacteria in a rectangular dish, each grows as a circle until it hits a wall or another bacterium. Find the time at which the first collision occurs, the median collision, and the last collision.

## Approach

- For each bacterium, compute the time it would collide with a wall from its distance to the nearest border minus 0.5 (the initial radius).
- Build a Delaunay triangulation and, for each vertex, find the shortest incident edge to determine when two bacteria first touch.
- The collision time for each bacterium is the minimum of wall and neighbor collision times.
- Sort all collision times and output the first, median, and last using ceiling of the square root.
