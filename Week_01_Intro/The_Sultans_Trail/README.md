# The Sultan's Trail

Given a sequence of n numbers and a target sum k, select exactly m non-overlapping contiguous subarrays each summing to k, and maximize the total length covered.

## Approach

Use a two-pointer sliding window to find all subarrays summing to k and record, for each endpoint j, the leftmost start `startIdx[j]`. Then run DP: `dp[i][j]` = maximum total length using exactly i+1 intervals, with the last one ending at or before position j. For each interval ending at j, extend the previous best from `dp[i-1][startIdx[j]-1]`.
