# Buddy Selection

Given n students each with c characteristics, pair them all into n/2 buddy pairs such that each pair shares more than f characteristics. Determine if the current pairing scheme is optimal (i.e., could a perfect matching exist that the students haven't found).

## Approach

Build a graph where an edge connects two students if they share more than f characteristics (checked via sorted-list merge). Run Edmonds' maximum cardinality matching. If the matching size equals n/2, a perfect matching exists and the current pairing is "not optimal"; otherwise print "optimal".
