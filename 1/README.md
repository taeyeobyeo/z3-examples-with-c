# Sudoku*

```
This project is designed for Z3 solver on Linux/Unix Environment.
```

## How to Use

### 1. to test out different variation change 'input' file
'input' file should be written in following form:
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

### 2. quick commands
```
1. gcc sudoku-LIA.c
2. ./a.out
```

### 3. error if ~
```
1. there is no preset file.
2. Z3 is not installed.
```
