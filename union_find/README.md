# [Union-Find (Disjoint sets)](https://liu.kattis.com/courses/AAPS/AAPS25/assignments/t7dpmj/problems/unionfind)

## Problem

Implement a data structure to handle disjoint sets. When the data structure is created, all elements are in their own sets. 

### Input

The first line of input consists of two integers `N` and `Q`, where `1 ≤ N ≤ 1000000` is the number of elements in the base set and `0 ≤ Q ≤ 1000000` is the number of operations. Then follow `Q` lines, one per operation. There are two types of operations:

- `“\= a b”` indicate that the sets containing `a` and `b` are joined
    
- `“? a b”` is a query asking whether `a` and `b` belong to the same set

In both cases, `a` and `b` are distinct integers between 0 and `N−1`.

### Output

For each query output a line containing “yes” if `a` and `b` are in the same set, and “no” otherwise.


### Sample Input 1 

```bash
10 4
? 1 3
= 1 8
= 3 8
? 1 3

```

### Sample Output 1

```bash
no
yes

```

### Sample Input 2

```bash
4 5
? 0 0
= 0 1
= 1 2
= 0 2
? 0 3

```

### Sample Output 2

```bash
yes
no

```

