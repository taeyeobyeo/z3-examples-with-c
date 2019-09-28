# Fill-A-Pix

```
This project is designed for Z3 solver on Linux/Unix Environment.
```

## How to Use

### to test out different variation, modify 'input' file
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


### quick commands
```
1. gcc fill-a-pix.c
2. ./a.out
```

### error if ~
```
1. there is no preset file.
2. Z3 is not installed.
```
