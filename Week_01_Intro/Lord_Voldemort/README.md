# Lord Voldemort

Given n intervals on a line, find the maximum number of intervals that overlap at any single point.

## Approach

Sweep line: create events for each interval's start and end, sort them (starts before ends at same position), then scan through incrementing a counter on start and decrementing on end. Track the maximum counter value.
