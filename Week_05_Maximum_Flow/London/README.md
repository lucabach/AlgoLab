# London

A newspaper has two sides; cut out letters to write a message. Determine whether enough letters exist across both pages (where each cut gives one letter from side 1 and one from side 2).

## Approach

Model with max-flow: source -> each letter-pair node (one node per (front, back) pair, capacity = number of such cuts), pair node -> letter nodes for both letters (capacity = count), letter nodes -> sink (capacity = required letter count for the message). If total flow equals message length, output "Yes".
