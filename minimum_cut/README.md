# [Minimum Cut](https://liu.kattis.com/courses/AAPS/AAPS25/assignments/uqu3ow/problems/mincut)

### Problem
Given a directed weighted graph and two vertices $s$, $t$, the goal is to find a subset $U$ of the vertices such that $s \in U$, $t \not\in U$, and the weight of edges from $U$ to $\overline{U}$ is minimized.

### Input
The first line of input contains four non-negative integers, $2 <= n <= 500$, $0 <= m <= 10\, 000$, $0 <= s <= n-1$ and $0 <= t <= n-1$, separated by single spaces, where $n$ is the numbers of nodes in the graph, $m$ is the number of edges, $s$ is the source and $t$ is the sink ($s \ne t$). Nodes are numbered from $0$ to $n-1$. Then follow $m$ lines, each line consisting of three (space-separated) integers $u$, $v$ and $w$ indicating that there is an edge from $u$ to $v$ in the graph with weight $1 <= w <= 10^8$.

### Output
Output should begin with a line containing an integer $k$, giving the size of $U$. Then follow $k$ lines giving the vertices in $U$, one per line. If there are multiple choices for $U$ any one will be accepted.
You may assume that there is a cut such that the total weight of edges from $U$ to $\overline{U}$ is less than $2^{31}$.

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