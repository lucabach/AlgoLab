# The Stymphalian Birds

Given n birds arranged in a binary heap structure, each with a kill deadline, determine whether Heracles can kill all birds in time by always targeting the bird with the earliest deadline.

## Approach

- Use a max-priority queue ordered by deadline (most urgent first). When a bird is killed, recursively kill its children in the heap (since they are nested inside it), counting total time spent.
- If at any point the time spent exceeds a bird's deadline before it is killed, output "no"; otherwise "yes."
