# [CD](https://liu.kattis.com/courses/AAPS/AAPS25/assignments/aoe934/problems/cd)

## Problem

Jack and Jill have decided to sell some of their Compact Discs, while they still have some value. They have decided to sell one of each of the CD titles that they both own. How many CDs can Jack and Jill sell?

Neither Jack nor Jill owns more than one copy of each CD.

### Input

The input consists of a sequence of test cases. The first line of each test case contains two positive **N** integers and **M**, each at most one **million**, specifying the number of CDs owned by Jack and by Jill, respectively. This line is followed by lines listing the catalog numbers of the CDs owned by Jack in increasing order, and more lines listing the catalog numbers of the CDs owned by Jill in increasing order. Each catalog number is a positive integer **no greater than one billion**. The input is terminated by a line containing two zeros. This last line is not a test case and should not be processed.

### Output

For each test case, output a line containing one integer, the number of CDs that Jack and Jill both own.

### Sample input 

```bash
3 3
1
2
3
1
2
4
0 0

```

### Sample output


```bash
2

```

### Several tests in one input

```
3 3
1
2
3
1
2
4

1 1
1
1

3 3
100
200
300
100
200
400

0 0
```

1. **Test Case 1**  
   - \(N=3\), \(M=3\)  
   - Jack’s CDs: `1`, `2`, `3`  
   - Jill’s CDs: `1`, `2`, `4`  
   - **Common CDs**: `1`, `2`  
   - **Intersection Count**: 2  

2. **Test Case 2**  
   - \(N=1\), \(M=1\)  
   - Jack’s single CD: `1`  
   - Jill’s single CD: `1`  
   - **Common CD**: `1`  
   - **Intersection Count**: 1  

3. **Test Case 3**  
   - \(N=3\), \(M=3\)  
   - Jack’s CDs: `100`, `200`, `300`  
   - Jill’s CDs: `100`, `200`, `400`  
   - **Common CDs**: `100`, `200`  
   - **Intersection Count**: 2  

### Output

```
2
1
2

```


