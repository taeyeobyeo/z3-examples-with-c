# Fill-A-Pix

```
This project is designed for Z3 solver on Linux/Unix Environment.
```

## How to Use

### 1. to test out different variation, modify 'input' file

The name of the file can be different.
'input' file should be written in following form:
```
? ? ? ? ?
? 9 ? ? ?
? 8 8 ? ?
? ? ? ? 4
4 ? 5 ? 2
```
This example is 5x5 input file. 
Every cells should be separated with a space character.
Unknown cells should be filled with '?'.

This file can be run with the program only as an stdio input.

### 2. Output
If the input is satisfiable. it will give upmost 5 solutions.
Other wise, the program will return regarding messages.

### 3. quick commands
```
1. gcc fill-a-pix.c
2. ./a.out < input
```

### 4. Warnings

Error could occur when...

```
1. there is no input file.
2. Z3 is not installed.
3. there is more than 1 line feed at the end of the file. (only 0 or 1 line feed can be consumed.)
```
