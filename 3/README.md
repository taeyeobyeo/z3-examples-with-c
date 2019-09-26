# Numbrix

```
This project is designed for Z3 solver on Linux/Unix Environment.
```

## How to Use

### to test out different variation change 'preset' file
'preset' file should be written in following form:
```
//start 
6 6
2 3 20
2 4 13
3 2 26
3 5 9
4 2 25
...
```

The first line should contain 2 integers which will be N and M of NxM grids.
There should be at least one space between two integers.

Other line has to be written in 3 positive integers with space in between.
The first digit represents the row number.
The second digit represents the column number.
The last digit represents the value of the cell.

### quick commands
```
1. gcc numbrix.c
3. ./a.out
4. z3 formula > result
5. gcc draw-numbrox.c
6. ./a.out
```

### error if ~
```
1. there is no preset file.
2. Z3 is not installed.
```
