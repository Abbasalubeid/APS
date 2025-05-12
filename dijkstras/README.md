# [Single source shortest path, non-negative weights](https://liu.kattis.com/courses/AAPS/AAPS25/assignments/uqu3ow/problems/shortestpath1)

### Input

The input consists of several test cases. Each test case starts with a line with four non-negative integers, $1 <= n <= 10 000$, $0 <= m <= 30 000$, $1 <= q <= 100$ and $0 <= s < n$, separated by single spaces, where $n$ is the numbers of nodes in the graph, $m$ the number of edges, $q$ the number of queries and $s$ the index of the starting node. Nodes are numbered from $0$ to $n-1$. Then follow $m$ lines, each line consisting of three (space-separated) integers $u$, $v$ and $w$ indicating that there is an edge from $u$ to $v$ in the graph with weight $0 <= w <= 1000$. Then follow $q$ lines of queries, each consisting of a single non-negative integer, asking for the minimum distance from node $s$ to the node number given on the query line.

Input will be terminated by a line containing four zeros, this line should not be processed.

### Output


### Sample Input 

```bash
4 3 4 0
0 1 2
1 2 2
3 0 2
0
1
2
3
2 1 1 0
0 1 100
1
0 0 0 0

```

### Sample Output 

```bash
0
2
4
Impossible

100

```