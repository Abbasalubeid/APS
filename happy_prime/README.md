# [Happy Happy Prime Prime](https://liu.kattis.com/courses/AAPS/AAPS25/assignments/foezmc/problems/happyprime)

## Problem

Any number that reduces to one when you take the sum of the square of its digits and continue iterating it until it yields 1 is a happy number. Any number that doesn’t, isn’t. A happy prime is both happy and prime.

For this problem you will write a program to determine if a number is a happy prime.

### Input
The first line of input contains a single integer $P$, ($1 \le P \le 10\, 000$), which is the number of data sets that follow. Each data set should be processed identically and independently.
Each data set consists of a single line of input. It contains the data set number, $K$, followed by the happy prime candidate, $m$, ($1 \le m \le 10\, 000$).


### Output
For each data set there is a single line of output. The single output line consists of the data set number, $K$, followed by a single space followed by the candidate, $m$, followed by a single space, followed by YES or NO, indicating whether $m$ is a happy prime.


### Sample Input 

```bash
4
1 1
2 7
3 383
4 1000

```

### Sample Output 

```bash
1 1 NO
2 7 YES
3 383 YES
4 1000 NO

```