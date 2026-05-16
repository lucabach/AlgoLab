# Fighting Pits of Meereen

Assign n fighters one by one to either the north or south pit; each assignment scores points based on how many fighters are in that pit and how well the fighter matches the current gate. Maximize total score while keeping the queue lengths within 11 of each other.

## Approach

Memoized DP on state `(total_assigned, north_count - south_count, north_gate, south_gate)`. At each step, try sending the next fighter north or south, compute the score using the pit's current queue length and gate state, and recurse. The gate encodes the last two fighters assigned to that pit (for bonus scoring). Cache with a 4D memo table.
