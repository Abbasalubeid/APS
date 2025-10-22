# [Cudak](https://liu.kattis.com/courses/AAPS/AAPS25/assignments/y86kt5/problems/cudak)

## Problem

Božo is a strange little boy. Every day he tires his friends with strange questions. Today’s question is: how many integers in the interval $[A, B]$ are there such that the sum of their digits is $S$, and which is the smallest such number?
Write a program that answers Božo’s question so that he can get some sleep.

### Input

The input contains three integers $A$, $B$ and $S$ ($1 <= A <= B < 10^{15}$, $1 <= S <= 135$).

### Output

The first line should contain the number of integers in the interval with the digit sum equal to $S$.
The second line should contain the smallest such integer.
The input data will guarantee that the first number is at least $1$.

### Sample Input 

```bash
1 9 5
```

### Sample Output 

```bash
1
5

```


### Sample Input 2 

```bash
1 100 10
```

### Sample Output 2

```bash
9
19

```