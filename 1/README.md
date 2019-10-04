# Sudoku*

```
This project is designed for Z3 solver on Linux/Unix Environment.
```

## How to Use

### 1. to test out different variation change 'input' file

The name of the file can be different.
But 'input' file should be written in following form:
```
? 2 ? 5 ? * ? 9 ?
8 ? ? 2 ? 3 ? ? 6
? 3 ? ? 6 ? * 7 ?
* ? ? ? * ? 6 ? ?
5 4 ? ? ? ? ? 1 9
? ? 2 ? ? ? 7 ? ?
? 9 * ? 3 ? ? 8 ?
2 ? ? 8 ? 4 ? * 7
? 1 ? 9 ? 7 ? 6 ?
```

Every cells should be separated with a space character.
Unknown cells should be filled with a '?' character.
The value of a cell is limited to ?, 0-9, or *.

### 2. Output/results

If the input is satisfiable, it will produce such result as following:

```
A separate output file has been created.

-------------------------
| 4 2 6 | 5 7 1 | 3 9 8 |
| 8 5 7 | 2 9 3 | 1 4 6 |
| 1 3 9 | 4 6 8 | 2 7 5 |
-------------------------
| 9 7 1 | 3 8 5 | 6 2 4 |
| 5 4 3 | 7 2 6 | 8 1 9 |
| 6 8 2 | 1 4 9 | 7 5 3 |
-------------------------
| 7 9 4 | 6 3 2 | 5 8 1 |
| 2 6 5 | 8 1 4 | 9 3 7 |
| 3 1 8 | 9 5 7 | 4 6 2 |
-------------------------
```

Notice that there will be only one output produced.
If the input is unsatisfactory, the program will give an message indicating unsatisfiability of the input.

### 3. quick commands
```
1. gcc sudoku-LIA.c
2. ./a.out < input
```

### 4. Warnings
```
1. there is no preset file.
2. Z3 is not installed.
```
