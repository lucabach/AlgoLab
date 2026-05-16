# Week 5 — Maximum Flow

Maximum flow is one of the most powerful and flexible algorithmic tools. The key skill is **graph modeling**: once you can express a problem as a flow network, BGL's push-relabel algorithm does the heavy lifting.

Classic reductions: bipartite matching → flow, feasibility problems → flow with lower bounds, connectivity → flow (min-cut = max-flow).

---

## Problems

| Problem | Core Technique | Status |
|---------|---------------|--------|
| [Tiles](Tiles/) | Bipartite matching via max flow (chessboard tiling) | Complete |
| [Coin Tossing Tournament](Coin_Tossing_Tournament/) | Flow feasibility — tournament scheduling | Complete |
| [London](London/) | Max flow — letter/word matching with capacities | Complete |
| [Knights](Knights/) | Bipartite matching — knight attacks on chessboard | Complete |
| [Augean Stables](Augean_Stables/) | Binary search + flow — cleaning schedule | Complete |

---

## Key Concepts

### Push-Relabel Max Flow (BGL)
```cpp
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
    boost::no_property,
    boost::property<boost::edge_capacity_t, long,
    boost::property<boost::edge_residual_capacity_t, long,
    boost::property<boost::edge_reverse_t, boost::graph_traits<Graph>::edge_descriptor>>>>
    Graph;

// Add edge with reverse (required by push-relabel)
auto add_edge = [&](int u, int v, long cap) {
    auto e = boost::add_edge(u, v, G).first;
    auto rev = boost::add_edge(v, u, G).first;
    boost::get(boost::edge_capacity, G)[e] = cap;
    boost::get(boost::edge_capacity, G)[rev] = 0;
    boost::get(boost::edge_reverse, G)[e] = rev;
    boost::get(boost::edge_reverse, G)[rev] = e;
};

long flow = boost::push_relabel_max_flow(G, source, sink);
```

### Bipartite Matching = Max Flow
Add source → left nodes (cap 1), right nodes → sink (cap 1), left → right edges (cap 1). Max flow = max matching.

### Min-Cut Interpretation
After max flow, edges crossing from reachable to non-reachable in the residual graph form the minimum cut. Use this to find bottlenecks or separating sets.
