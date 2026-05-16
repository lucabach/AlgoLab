# Rapunzel

Given a tree where each node has a brightness value, find all nodes that lie on a path of length exactly m whose brightness range (max - min) is at most k.

## Approach

- For each leaf, trace the path to the root, maintaining a sliding window of size m using two max-priority queues tracking the minimum and maximum brightness in the window.
- Mark a node as "safe" if the window ending at that node has max - min ≤ k. Stop early once a node has already been visited in a previous leaf's traversal.
- Output all safe nodes (or "Abort mission" if none).
