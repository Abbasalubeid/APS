# [Single source shortest path, negative weights](https://liu.kattis.com/courses/AAPS/AAPS25/assignments/uqu3ow/problems/shortestpath3)

### Input
The input consists of several test cases. Each test case starts with a line with four non-negative integers, $1 <= n <= 1000$, $0 <= m <= 5000$, $1 <= q <= 100$ and $0 <= s < n$, separated by single spaces, where $n$ is the numbers of nodes in the graph, $m$ the number of edges, $q$ the number of queries and $s$ the index of the starting node. Nodes are numbered from 0 to $n-1$. Then follow $m$ lines, each line consisting of three (space-separated) integers $u$, $v$ and $w$ indicating that there is an edge from $u$ to $v$ in the graph with weight $-2000 <= w <= 2000$. Then follow $q$ lines of queries, each consisting of a single non-negative integer, asking for the minimum distance from node $s$ to the node number given on the query line.

Input will be terminated by a line containing four zeros, this line should not be processed.

### Output
For each query, output a single line containing the minimum distance from node $s$ to the node specified in the query, the word “Impossible” if there is no path from $s$ to that node, or “-Infinity” if there are arbitrarily short paths from $s$ to that node. For clarity, the sample output has a blank line between the output for different cases.


### Sample Input 

```bash
5 4 3 0
0 1 999
1 2 -2
2 1 1
0 3 2
1
3
4
2 1 1 0
0 1 -100
1
0 0 0 0

```

### Sample Output 

```bash
-Infinity
2
Impossible

-100

```