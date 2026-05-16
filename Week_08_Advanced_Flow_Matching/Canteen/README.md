# Canteen

Given a canteen serving students over n days, with daily food supply costs and student demands with meal prices, determine whether all students can be served and at what maximum profit.

## Approach

- Model as a min-cost flow: source connects to each day's supply (capacity = portions available, cost = preparation cost), each day connects to the next for leftover food (capacity and storage cost), and each day's demand drains to the sink with a profit.
- Run successive shortest paths; check if total flow equals total student demand and compute net profit from the flow cost.
