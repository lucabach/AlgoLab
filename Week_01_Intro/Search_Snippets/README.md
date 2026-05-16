# Search Snippets

Given n words, each appearing at multiple positions in a document, find the shortest snippet (contiguous range of positions) that contains at least one occurrence of every word.

## Approach

Use a sliding window over positions with a min-heap. At each step, track the current minimum position across all words and the global maximum. The window length is `max - min + 1`. Pop the word with the smallest current position, advance it to its next occurrence, and update the max. Stop when any word runs out of positions. Track the minimum window length seen.
