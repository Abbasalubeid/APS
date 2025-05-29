# [Fenwick Tree](https://liu.kattis.com/courses/AAPS/AAPS25/assignments/t7dpmj/problems/fenwick)

## Problem

A Fenwick Tree (also known as a Binary Indexed Tree) is a data structure on an array which enables fast (O(logn)) updates and prefix sum queries on the underlying data.

For this problem, implement a Fenwick Tree to support operations of two types: (a) increment an element in the array or (b) query the prefix sum of a portion of the array.

### Input

The first line of input contains two integers N, Q, where 1 ≤ N ≤ 5000000 is the length of the array and 0 ≤ Q ≤ 5000000 is the number of operations. Then follow Q lines giving the operations. There are two types of operations:

- `+ i δ` indicates that a[i] is incremented by δ, where 0 ≤ i < N and −10^9 ≤ δ ≤ 10^9 (both are integers)
- `? i` is a query for the value of a[0]+ a[1] + … + a[i−1], where 0 ≤ i ≤ N (for i =0 this is interpreted as an empty sum)

You should assume that every array entry is initially 0.

### Output

For each query in the input, output one line giving the answer to that query.

### Sample Input 

```bash
10 4
+ 7 23
? 8
+ 3 17
? 8

```

### Sample Output 

```bash
23
40

```

### Sample Input 2

```bash
5 4
+ 0 -43
+ 4 1
? 0
? 5

```

### Sample Output 2

```bash
0
-42

```
