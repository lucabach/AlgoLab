# Moving Books

n friends help move m books; each friend can carry books up to their strength, and each round takes 3 minutes. Find the minimum total time to move all books.

## Approach

Sort strengths and weights descending. If the heaviest book exceeds the strongest friend's strength, output "impossible". Otherwise binary search on the number of books carried per friend per round. For each candidate, compute how many friends are needed (ceiling division) and check if the i-th friend can carry the i-th heaviest book. Output `(rounds * 3) - 1` minutes.
