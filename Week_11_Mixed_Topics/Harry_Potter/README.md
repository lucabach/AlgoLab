# Harry Potter

Given a network of wizards exchanging magical substances through intermediate nodes, find the minimum number of people needed in the network and the minimum suspicion level to move a required amount from person 1 to person 2.

## Approach

- Binary search on the network size k (how many of the n people are in use). For each candidate k, formulate a linear program enforcing flow conservation, exchange rate constraints, a total suspicion budget, and a per-exchange suspicion bound.
- Solve the LP with CGAL to check feasibility and extract the minimum suspicion value. Report the smallest k for which a solution exists.
