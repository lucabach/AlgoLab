# Week 9 — Minimum-Cost Flow

Min-cost flow finds the cheapest way to send a required amount of flow through a network. It generalizes both shortest paths and max flow, so many scheduling and assignment problems reduce to it.

---

## Problems

| Problem | Core Technique | Status |
|---------|---------------|--------|
| [DHL](DHL/) | Min-cost flow — package routing with costs | Complete |
| [Fleetrace](Fleetrace/) | Min-cost flow — boat-sailor assignment | Complete |
| [Targaryen](Targaryen/) | Min-cost flow — army supply scheduling | Complete |
| [Hong Kong](Hong_Kong/) | Min-cost flow — balloon delivery | Complete |

---

## Key Concepts

### BGL Successive Shortest Paths
```cpp
#include <boost/graph/successive_shortest_path_nonneg_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

boost::successive_shortest_path_nonneg_weights(G, source, sink);
long cost = boost::find_flow_cost(G);
```
Edge properties needed: `capacity`, `residual_capacity`, `weight`, `reverse`.

### When to Use Min-Cost Flow
- You need both a feasibility/quantity constraint AND a cost to minimize
- Assignment problems where matches have different costs
- Scheduling problems where earliness/lateness has a penalty
