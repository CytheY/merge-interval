# Merge intervals

This repository contains a small C++ program implementing a MERGE function which takes a list of intervals and returns a result set of overlapping intervals merged into each other based on their lower 
and upper boundaries. All non overlapping intervals remain untouched and are simply added to the result set. 
It is assumed that the order of the intervals in the result set is irrelevant.

Example:
 Input: [25,30] [2,19] [14,23] [4,8] -> Output [2,23] [25,30]

The approach of solving this is to compare every interval in the input set with each other and check for three cases:
1. The current interval is a subinterval of some other compared interval. In this case the current interval can be discarded from the set.
   Example:  [4,8] is in the range of [14,23], so [4,8] can be discarded.

2. The current intervals boundaries overlap with some other compared intervals boundaries. In this case the lowest and the highest boundaries are used to update the compared intervals boundaries and the current interval is discarded from the set.
   Example: [2,19] [14,23] - > [2,23]

3. The current interval is neither a subinterval of some other compared interval nor overlaps with some other compared interval. The current interval simply remains in the set.

Questions: 
- What is the runtime of the program?
  
  Since two nested for loops are used to interate over every interval and compare
  it to every other interval the runtime of the program can be estimated by O(N^2).

- How can the robustness be ensured especially with regards to very large input sets?

  While not implemented, to ensure the robustness with very large input sets, the input set 
  could be splitted into smaller sets which would be merged one after another. The 
  resulting sets are then merged again and so on until a single result set remains.
  This way possible memory overflows could be prevented.

- How performs the memory consumption of the program?

  Since only a single array is used to perform operations the memory consumption is
  linear to the intervals to be merged. So the memory cunsumption can be estimated by O(N).

## How to run

To run the program you simply checkout the repository and compile the main.cpp it with g++:

```
sudo g++ -o main main.cpp
```

The program is then executed by:

```
./main
```
