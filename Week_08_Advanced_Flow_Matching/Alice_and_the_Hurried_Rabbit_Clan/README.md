# Alice and the Hurried Rabbit Clan

Given an n×m grid with values, find the minimum cost path from the top-left to the bottom-right where moves are right or down and cost depends on accumulated row and column sums.

## Approach

- Precompute horizontal and vertical prefix sums where each entry accumulates the sum of all elements above/left (triangular sums, not simple prefix sums).
- Use DP where dp[i][j] is the minimum cost to reach cell (i,j), transitioning from the left (adding a vertical cumulative sum) or from above (adding a horizontal cumulative sum).
