# [Maximum Flow](https://liu.kattis.com/courses/AAPS/AAPS25/assignments/uqu3ow/problems/maxflow)

### Input
The first line of input contains a line with four non-negative integers, $2 <= n <= 500$, $0 <= m <= 10\, 000$, $0 <= s <= n-1$ and $0 <= t <= n-1$, separated by single spaces, where $n$ is the numbers of nodes in the graph, $m$ is the number of edges, $s$ is the source and $t$ is the sink ($s != t$). Nodes are numbered from $0$ to $n-1$. Then follow $m$ lines, each line consisting of three (space-separated) integers $u$, $v$ and $c$ indicating that there is an edge from $u$ to $v$ in the graph with capacity $1 <= c <= 10^{8}$.


### Output
The output should begin with a line containing three integers $n$, $f$, and $m’$. $n$ is the number of nodes in the flow graph (same as in input), $f$ is the size of a maximum flow from node $s$ to node $t$ in the flow graph, and $m’$ is the number of edges used in the solution. You may assume that $f < 2^{31}$.

Then there should be $m’$ lines, each containing three integers $u$, $v$ and $x$, indicating that $x$ units of flow are transported from $u$ to $v$. $x$ must be greater than $0$ and at most as big as the capacity from $u$ to $v$. Each pair of vertices $(u, v)$ should be given at most once in the output.

### Sample Input 

```bash
4 5 0 3
0 1 10
1 2 1
1 3 1
0 2 1
2 3 10

```

### Sample Output 

```bash
4 3 5
0 1 2
0 2 1
1 2 1
1 3 1
2 3 2

```