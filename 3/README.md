# Numbrix

```
This project is designed for Z3 solver on Linux/Unix Environment.
```

## How to Use

### 1. to test out different variation change 'input' file
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

### 2. quick commands
```
1. gcc numbrix.c
2. ./a.out
```

### 3. error if ~
```
1. there is no input file.
2. Z3 is not installed.
```
