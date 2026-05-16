# Worm Kingdom

Given k trees (one per burrow), each with weighted nodes, split the kingdom into two parts by cutting one tree edge or selecting whole burrows, minimizing the imbalance (absolute difference in total size between the two parts) plus a penalty p per cut inter-burrow connection.

## Approach

For k=1, DFS to find all subtree sums and find the edge cut minimizing the difference. For k>1, use a knapsack DP over whole burrows (dp0) and collect all possible single subtree cuts across all trees (dp1). Combine: for each achievable partial sum x (from either source), the best split difference is |S - 2x|, then add p*(k-1) for the inter-burrow cuts.
