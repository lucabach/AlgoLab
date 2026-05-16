# Even Pairs

Given a sequence of numbers, count the number of pairs (i, j) with i <= j such that the sum of elements from index i to j is even.

## Approach

Use prefix sums (mod 2). A subarray sum is even iff the prefix sum at both ends has the same parity. Count how many prefix sums (including the empty prefix) are even (`e`) and how many are odd (`o`). The answer is C(e, 2) + C(o, 2).
