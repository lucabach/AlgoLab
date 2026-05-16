# Dominoes

A row of dominoes each with a height; pushing domino 0 topples all dominoes it can reach (and each toppled domino may reach further ones). Count how many dominoes fall in total (including domino 0).

## Approach

Linear scan tracking the furthest reach so far. Domino `i` is toppled if `i <= max_reach`. Whenever a domino is toppled, extend `max_reach = max(max_reach, i + height[i] - 1)`. The answer is `min(max_reach + 1, n)`.
