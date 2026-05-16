# Evolution

Given an evolutionary tree where each species has an age, answer queries of the form "find the oldest ancestor of species X with age at most Y."

## Approach

- Build the tree from parent-child relationships and attach queries to their target nodes.
- Run a DFS, maintaining a stack of (node, age) pairs on the current root-to-node path.
- For each query at a node, binary search the stack for the oldest ancestor whose age is within the bound. The result is read off in O(log n) per query.
