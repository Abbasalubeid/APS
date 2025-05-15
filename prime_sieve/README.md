# [Prime Sieve](https://liu.kattis.com/courses/AAPS/AAPS25/assignments/q25tc9/problems/primesieve)

### Input

The first line of input consists of two integers $n$, $q$, where $1 <= n <= 10^8$ and $1 <= q <= 20000$. Then follow $q$ lines, each containing an integer $x$ satisfying $1 <= x <= n$.

### Output

On the first line of output, write one line giving the number of prime numbers less than or equal to $n$. Then for each query $x$, output $1$ if $x$ is a prime and ouput $0$ if $x$ is composite.

### Sample Input 

```bash
9973 6
1
2
3
4
9972
9973

```

### Sample Output 

```bash
1229
0
1
1
0
0
1

```