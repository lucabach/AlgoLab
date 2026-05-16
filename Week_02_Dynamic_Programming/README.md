# Week 2 — Dynamic Programming

Dynamic programming (DP) is about breaking a problem into overlapping subproblems, solving each once, and storing the result. The key insight is always: **what is the state, and how does it transition?**

This week covers classic DP formulations: interval DP (optimal play on a sequence), DP with memoisation, and multi-dimensional state spaces.

---

## Problems

| Problem | Core Technique | Status |
|---------|---------------|--------|
| [Burning Coins](Burning_Coins/) | Interval DP — two-player optimal game on a coin row | Complete |
| [Greyjoy](Greyjoy/) | Sliding window on sequences | Incomplete |
| [San Francisco](San_Francisco/) | DP on DAG — maximize score with limited steps | Incomplete |
| [Severus Snape](Severus_Snape/) | DP on sequences — potion scheduling | Complete |
| [Fighting Pits of Meereen](Fighting_Pits_of_Meereen/) | DP with circular state — fighter scheduling | Complete |
| [Planet Express](Planet_Express/) | BFS on compressed state space | Complete |

---

## Key Concepts

### Interval DP
State: `dp[i][j]` = optimal value over the sub-sequence `[i, j]`.
Transition: try all ways to split or choose from the ends.
Direction: fill by increasing interval length (bottom-up).

```cpp
for (int len = 1; len < n; len++)
    for (int i = 0; i + len < n; i++) {
        int j = i + len;
        dp[i][j] = max(dp[i+1][j] + val[i], dp[i][j-1] + val[j]);
    }
```

### Two-Player Games
When two players play optimally, model as: on your turn, maximize; on opponent's turn, minimize (or track whose turn it is via the interval length's parity).

### DAG DP
Topologically sort the state graph, then propagate values forward. Useful when states have clear dependencies.
