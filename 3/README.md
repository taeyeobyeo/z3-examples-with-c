# Numbrix

```
This project is designed for Z3 solver on Linux/Unix Environment.
```

## How to Use

### 1. to test out different variation change 'input' file

The name of the file can be different.
'input' file should be written in following form:

```
? ? ? ? ? ?
? ? 20 13 ? ?
? 26 ? ? 9 ?
? 25 ? ? 10 ?
? ? 23 36 ? ?
? ? ? ? ? ?
```
This example is 6x6 input file.
Every cells in a row should be separated with a space character.
the unknown cells should be written as '?'.

This file can be run with the program only as an standard input as file.
```
./a.out < input
```
### 2. Output/Results

If the input is satisfiable, it will produce such result as following:.

```
A separate output file has been created

17 16 15 14  7  6
18 19 20 13  8  5
27 26 21 12  9  4
28 25 22 11 10  3
29 24 23 36 35  2
30 31 32 33 34  1
```

Notice that there will be only one output produced.
If the input is unsatisfactory, the program will give an message indicating unsatisfiability of the input.

### 3. quick commands
```
1. gcc numbrix.c
2. ./a.out < input
```

### 4. error if ~


Error could occur when...

```
1. there is no input file.
2. Z3 is not installed.
3. there is more than 1 line feed at the end of the file. (only 0 or 1 line feed can be consumed.)
```
