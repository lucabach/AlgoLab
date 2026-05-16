# Placing Knights

Given an n×n chessboard with some squares removed, find the maximum number of knights that can be placed so no two attack each other.

## Approach

- Knights on a chessboard only attack squares of the opposite color (in the standard 2-coloring), so the attack graph is bipartite.
- Connect even-colored squares to odd-colored squares via max-flow edges wherever a knight attack exists, using source/sink to enforce one knight per square.
- The answer is (total present squares) minus the maximum bipartite matching (max-flow value).
