This is simple script to find files by regex, save newest, deleting older ones.
Writen in **C++17**.

### Compiling
```
$ mkdir build
$ cd ./build
$ cmake ../
$ make
```

### Usage
```
$ LastFile -h
$ LastFile --help
```
```
$ ./LastFile <path_to_files>
$ ./LastFile <path_to_files> [regex]
```
Alternatively regex may be passed in `main.cpp`.
`
### Example
```
& ./LastFile . .*abc.*
```
