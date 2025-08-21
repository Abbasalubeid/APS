# [Knapsack](https://liu.kattis.com/courses/AAPS/AAPS25/assignments/t7dpmj/problems/knapsack)

## Problem

Implement a solution to the classic knapsack problem. You are given a knapsack that can hold up to a certain weight (its capacity), and several items you may choose to put in the knapsack. Each item has a weight and a value. Choose a subset of the items (which could be all of them, or none of them) having the greatest value that fit into the knapsack (i.e. the sum of the weights of the items you choose must be less than or equal to the knapsack capacity).


### Input

The input consists of between $1$ and $30$ test cases. Each test case begins with an integer $1 \le C \le 2\, 000$, giving the capacity of the knapsack, and an integer $1 \le n \le 2\, 000$, giving the number of objects. Then follow $n$ lines, each giving the value and weight of the $n$ objects. Both values and weights are integers between $1$ and $10\, 000$.

### Output

For each test case, output a line containing the number of items chosen, followed by a line containing the indices of the chosen items (the first item has index , the second index , and so on). The indices can be given in any order.


### Sample Input 

```bash
5 3
1 5
10 5
100 5
6 4
5 4
4 3
3 2
2 1

```

### Sample Output 

```bash
1
2
3
1 2 3

```