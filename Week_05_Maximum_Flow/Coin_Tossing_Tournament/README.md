# Coin Tossing Tournament

Given m matches between n players (some with known outcomes, some undecided), determine if it is possible to assign winners to undecided matches such that each player ends with exactly their given final score.

## Approach

Model with max-flow: source -> each match (capacity 1), each match -> its possible winner(s) (capacity 1 each), each player -> sink (capacity = required final score). For decided matches, only one player can receive the point. If max-flow equals m and total scores sum to m, output "yes".
