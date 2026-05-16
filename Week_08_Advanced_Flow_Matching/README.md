# Week 8 — Advanced Flow & Matching

This week combines flow networks with more complex modeling, including general graph matching, flow with lower bounds, and problems that require combining flow with geometry or DP.

The key skill is recognizing which flow model fits a problem, then handling the bookkeeping carefully (lower bounds, multiple sources/sinks, etc.).

---

## Problems

| Problem | Core Technique | Status |
|---------|---------------|--------|
| [Lions vs Hyenas](Lions_vs_Hyenas/) | Max flow — territory assignment | Complete |
| [Placing Knights](Placing_Knights/) | Bipartite matching — maximum independent set | Complete |
| [Real Estate Market](Real_Estate_Market/) | Max flow / assignment — buyer-property matching | Complete |
| [Canteen](Canteen/) | Min-cost flow — supply/demand scheduling | Complete |
| [Algocoon](Algocoon/) | Min-cut on multi-component graph | Complete |
| [Alice and the Hurried Rabbit Clan](Alice_and_the_Hurried_Rabbit_Clan/) | Flow + timing constraints | Complete |

---

## Key Concepts

### Maximum Independent Set (Bipartite)
By König's theorem: in a bipartite graph, `max independent set = n - max matching`. Model as flow, compute matching, then find independent set from the min-cut structure.

### Flow with Lower Bounds
Transform: for an edge with lower bound `l` and upper bound `u`, subtract `l` from the capacity, adjust source/sink demands. Add a super-source/super-sink to restore feasibility.

### Min-Cut for Separation
After running max flow, the min-cut tells you which nodes/edges to remove to disconnect source from sink. Useful for "what is the minimum number of X to block Y?"

### Multi-Component Flow
Some problems have multiple disconnected components. Run flow independently on each and combine results, or add a super-source connecting to all component sources.
