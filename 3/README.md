# Numbrix

```
This project is designed for Z3 solver on Linux/Unix Environment.
```

## How to Use

#### warning

```
This program only supports maximum of 9x9 grid numbrix puzzle
```

### to test out different variation change 'input' file
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

### quick commands
```
1. gcc numbrix.c
2. ./a.out
```

### error if ~
```
1. there is no input file.
2. Z3 is not installed.
```
