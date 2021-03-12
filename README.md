# DataStructuresExam
## Compile

1. Clone the repository

```shell
git clone https://github.com/shoriwe-upb/DataStructuresExam.git
```

2. Change the current working directory

```shell
cd DataStructuresExam
```

3. Compile it using

Notice that I compile it in Windows using `mingw_w64-dwarf`

```shell
gcc -I include main.c -o solution.exe
```

## Test

1. Execute the compiled binary

```shell
solution.exe
```

2. Pass to it the map

```shell
1 1 1 1 1 1 1 1 1 1 1
1 0 0 0 0 0 1 0 0 0 1
1 0 1 0 0 0 1 0 1 0 1
e 0 1 0 0 0 0 0 1 0 1
1 0 1 1 1 1 1 0 1 0 1
1 0 1 0 1 0 0 0 1 0 1
1 0 0 0 1 0 1 0 0 0 1
1 1 1 1 1 0 1 0 0 0 1
1 0 1 m 1 0 1 0 0 0 1
1 0 0 0 0 0 1 0 0 0 1
1 1 1 1 1 1 1 1 1 1 1
```

3. Receive the output

```shell
[8:3][9:3][9:4][9:5][8:5][7:5][6:5][5:5][5:6][5:7][6:7][7:7][8:7][9:7][9:8][8:8][7:8][6:8][6:9][5:9][4:9][3:9][2:9][1:9][1:8][1:7][2:7][3:7][3:6][3:5][2:5][1:5][1:4][2:4][3:4][3:3][2:3][1:3][1:2][1:1][2:1][3:1][3:0]
```

