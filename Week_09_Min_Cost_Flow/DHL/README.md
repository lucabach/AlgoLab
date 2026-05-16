# DHL

Given two sequences of delivery stops with associated costs, find the minimum total cost to pair them up using a DP alignment.

## Approach

- Use a 2D DP where dp[i][j] is the minimum cost to handle the first i stops from sequence A and j stops from sequence B.
- At each cell, the cost added is (a[i]-1)*(b[j]-1), and transitions come from dp[i-1][j-1], dp[i-1][j], or dp[i][j-1].
