# Kingdom Defense

Given a network of locations with garrisons and defense requirements, and paths with minimum and maximum troop flow constraints, determine if it is feasible to route troops so that every location's defense demand is met.

## Approach

Model as a flow feasibility problem with lower bounds. For each path, subtract the lower bound from capacity and adjust node demands. Add a super-source and super-sink to handle the demand imbalances. Run max-flow; if it saturates all demand edges, the assignment is feasible.
