# [Evil Straw Warts Live](https://liu.kattis.com/courses/AAPS/AAPS25/assignments/ix25ua/problems/evilstraw)

## Problem

A palindrome is a string of symbols that is equal to itself when reversed. Given an input string, not necessarily a palindrome, compute the number of swaps necessary to transform the string into a palindrome. By swap we mean reversing the order of two adjacent symbols. For example, the string “mamad” may be transformed into the palindrome “madam” with 3 swaps:

- swap “ad” to yield “mamda”

- swap “md” to yield “madma”

- swap “ma” to yield “madam”

### Input

The first line of input gives $1 <= n <= 200$, the number of test cases. For each test case, one line of input follows, containing a string of up to $100$ lowercase letters.


### Output

Output consists of one line per test case. This line will contain the number of swaps, or “Impossible” if it is not possible to transform the input to a palindrome.

### Sample Input 

```bash
3
mamad
asflkj
aabb

```

### Sample Output 

```bash
3
Impossible
2

```