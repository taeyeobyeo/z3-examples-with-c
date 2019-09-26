# Sudoku*

```
This project is designed for Z3 solver on Linux/Unix Environment.
```

## How to Use

### to test out different variation change 'preset' file
'preset' file should be written in following form:
```
//start 
122
145
16*
156
...
```

The first line should be filled with an comment. 
Other lines are formed with 3 integers such as 122.
first integer indicates the row #. 
second integer indicates the column #. 
the last integer indicates value or an asterisk mark. 

### quick commands
```
1. cd LIA
2. gcc sudoku-LIA.c
3. ./a.out
4. z3 formula > result
5. gcc draw-LIA.c
6. ./a.out
```

### error if ~
```
1. there is no preset file.
2. Z3 is not installed.
```
