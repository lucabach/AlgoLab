# Burning Coins

Two players alternate picking coins from either end of a row; find the maximum value you can collect assuming both play optimally.

## Approach

Interval DP: `dp[i][j]` = max coins you collect from subarray `i..j` when it is your turn. On your turn take max of picking left or right coin. On the opponent's turn they minimize (pick the move leaving you less). Fill by increasing interval length, tracking whose turn it is based on parity.
