# Boats

Given n boats each with a length and a ring position, anchor as many boats as possible such that each boat's ring is at or after the previous boat's right end, and boats don't overlap.

## Approach

Sort boats by ring position. Greedily scan: for each boat, if its ring is past the current end, anchor it (place it as far left as possible while its ring is valid). If its ring is before the current end, try to swap it in if it results in a smaller right boundary. Track two pointers for the current and previous right endpoints to enable potential swaps.
