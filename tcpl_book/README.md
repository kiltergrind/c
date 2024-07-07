# The C Programming Language (K & R)

# Exercises
> All the most meaningful and challenging exercises code done by me

### 1. [Chapter 1](./exercises/chapter_1/)
### 2. [Chapter 2](./exercises/chapter_2/)

# How to build and run
## Requirements
- meson build system
- gcc / clang or other C compiler

### 1. Go to a specific chapter directory:
```sh
cd exercises/chapter_1
```

### 2. Prepare build environment
```sh
meson setup build
```

### 3. Go to the build directory, compile and run
```sh
cd build
meson compile
./ex_<N>
```
- or
```sh
meson compile -C build
./build/ex_<N>
```


> `ex_<N>` - is a name of compiled executable, where `N` is a specific number of exercise in the book