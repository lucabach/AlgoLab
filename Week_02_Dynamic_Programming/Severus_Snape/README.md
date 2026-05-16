# Severus Snape

Given two sets of potions (type A and type B), find the minimum total number of potions to achieve a required power P and wit W while satisfying happiness and stat constraints.

## Approach

- Precompute `DPA[i][j][h]` = max power achievable selecting exactly j type-A potions from the first i, with cumulative happiness at least h.
- Sort type-B potions by wit descending; accumulate wit greedily.
- For each count of B potions (adding one at a time) that reaches W, binary search / iterate over counts of A potions and check if the combined power and wit constraints are met. Output the minimum total.
