# Week 1 — Introduction: Prefix Sums & Sliding Window

The first week builds your intuition for two foundational techniques that underpin a huge class of competitive-programming problems: **prefix sums** (precomputing cumulative values to answer range queries in O(1)) and the **sliding window** (maintaining a running state over a moving subarray to avoid redundant recomputation).

These techniques are deceptively simple — but mastering them is essential because they appear as sub-steps inside nearly every harder algorithm you will encounter later.

---

## Problems

| Problem | Core Technique | Status |
|---------|---------------|--------|
| [Search Snippets](Search_Snippets/) | Sliding window — track word positions across document | Complete |
| [Dominoes](Dominoes/) | Prefix sums — row/column parity counts | Complete |
| [Even Pairs](Even_Pairs/) | Prefix sums — parity of prefix sums to count even-sum pairs | Complete |
| [Even Matrices](Even_Matrices/) | 2D prefix sums — extend Even Pairs to matrices | Complete |
| [The Sultan's Trail](The_Sultans_Trail/) | Sliding window over sorted sequence | Complete |
| [Lord Voldemort](Lord_Voldemort/) | Prefix sums + frequency counting | Complete |

---

## Key Concepts

### Prefix Sums
Given array `a[]`, build `prefix[i] = a[0] + ... + a[i-1]`. Then `sum(l, r) = prefix[r+1] - prefix[l]` in O(1). For 2D, extend to `prefix[i][j]` covering the rectangle from (0,0) to (i-1, j-1).

### Parity Trick
For "even-sum subarray" problems: note that `sum(l,r)` is even iff `prefix[l]` and `prefix[r+1]` have the same parity. This reduces the problem to counting pairs with matching parities.

### Sliding Window
Maintain a window `[l, r]` and expand/contract it. Use a `map<value, count>` or similar data structure to track the window state and avoid rescanning elements.

---

## Compilation

```bash
g++ -std=c++17 -O2 -o sol src/main.cpp
./sol < public/sample.in
```
