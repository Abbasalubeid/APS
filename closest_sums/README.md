# [Closest Sums](https://liu.kattis.com/courses/AAPS/AAPS25/assignments/aoe934/problems/closestsums)

## Problem

Given is a set of integers and then a sequence of queries. A query gives you a number and asks to find a sum of two distinct numbers from the set which is closest to the query number.

### Input

Input contains multiple cases. Each case starts with an integer `1<n≤1000`. The following `n` lines contain distinct integer numbers. The next line contains a positive integer `m` giving the number of queries, ` 0<m<25`. The next `m` lines contain an integer of the query, one per line. All the `n+m` integers are between **−107 and 107**, inclusive.

### Output

Output should be organized as in the sample below. For each query output one line giving the query value and the closest sum in the format as in the sample.

### Sample Input 

```bash
5
3
12
17
33
34
3
1
51
30
3
1
2
3
3
1
2
3
3
1
2
3
3
4
5
6

```

### Sample Output 

```bash
Case 1:
Closest sum to 1 is 15.
Closest sum to 51 is 51.
Closest sum to 30 is 29.
Case 2:
Closest sum to 1 is 3.
Closest sum to 2 is 3.
Closest sum to 3 is 3.
Case 3:
Closest sum to 4 is 4.
Closest sum to 5 is 5.
Closest sum to 6 is 5.

```