# Motorcycles

Motorcycles start at different y-positions on the y-axis and ride to the right with slopes determined by their start and end positions. Determine which motorcycles are never blocked (ride forever without being overtaken from behind).

## Approach

Sort motorcycles by starting y-position descending. Scan from both ends tracking the "best slope" (least steep absolute slope seen so far). A motorcycle is eliminated if a previously seen one with a steeper rise will eventually block it. Use exact rational arithmetic (CGAL Gmpq) to avoid floating-point errors in slope comparisons.
