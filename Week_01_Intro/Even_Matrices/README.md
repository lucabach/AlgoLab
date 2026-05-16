# Even Matrices

Given an n x n matrix of integers, count the number of sub-matrices whose element sum is even.

## Approach

Fix two row indices (start, end) and reduce to a 1D even-pairs problem on column prefix sums. For each column, compute the prefix sum of the row range. Then count pairs of columns where the prefix sums have the same parity using C(even, 2) + C(odd, 2). This runs in O(n^3).
