# Fill-A-Pix

```
This project is designed for Z3 solver on Linux/Unix Environment.
```

## How to Use

### to test out different variation change 'preset' file
'preset' file should be written in following form:
```
//start 
5 6
145
164
229
328
...
```

The first line should contain 2 integers which will be N and M of NxM grids.
There should be at least one space between two integers.

Othe numbers should be written in 3 digit numbers.
The first digit represents the row number.
The second digit represents the column number.
The last digit represents the number of black cells around the cell and the cell itself.

### quick commands
```
1. gcc fill-a-pix.c
3. ./a.out
4. z3 formula > result
5. gcc draw-pix.c
6. ./a.out
```

### error if ~
```
1. there is no preset file.
2. Z3 is not installed.
```
