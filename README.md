# Custom `printf`

A custom implementation of the C `printf` function written from scratch to understand how formatted output works internally.

This project does **NOT** rely on the C Standard Library for formatting or output. Instead, it manually processes variadic arguments using the x86 (32-bit) calling convention and writes output directly through Linux system calls.

## Features

- Support for `%s`
- Support for `%c`
- Support for `%d`
- Support for `%%` (literal `%`)
- Support for negative integers
- Manual variadic argument handling (**WITHOUT** `stdarg.h`)
- Direct Linux system calls for output
- No dependency on the C Standard Library for formatting

---

## Motivation

The goal of this project is to understand how `printf` actually works internally instead of simply using the implementation provided by the C Standard Library.

Topics explored include:

- x86 (32-bit) calling conventions
- Stack frames
- Variadic functions
- Pointer arithmetic
- Integer to string conversion
- Linux system calls
- Format string parsing

---

## Requirements

This project targets **32-bit Linux**.

Install the required packages on Ubuntu:

```bash
sudo apt update

sudo apt install \
    gcc \
    gcc-multilib \
    libc6-dev-i386 \
    make
```

Verify that your compiler supports 32-bit builds:

```bash
gcc -v
```

---

## Building

Compile using GCC:

```bash
gcc -m32 -O0 -fno-omit-frame-pointer printf.c -o printf
```

### Compiler flags

| Flag | Description |
|-------|-------------|
| `-m32` | Generate a 32-bit executable |
| `-O0` | Disable optimizations (easier debugging) |
| `-fno-omit-frame-pointer` | Preserve the stack frame (`EBP`) |

---

## Running

Execute the program:

```bash
./printf
```

---

## Example

```c
my_printf("Hello %s!\n", "World");
my_printf("Character: %c\n", 'A');
my_printf("Number: %d\n", 12345);
my_printf("Negative: %d\n", -12345);
my_printf("100%% Complete\n");
```

Output

```
Hello World!
Character: A
Number: 12345
Negative: -12345
100% Complete
```

---

## Project Structure

```
.
├── printf.c
├── README.md
└── .gitignore
```

---

## Current Status

Implemented

- [x] `%s`
- [x] `%c`
- [x] `%d`
- [x] `%%`
- [x] Negative integer support

Planned

- [ ] `%u`
- [ ] `%x`
- [ ] `%X`
- [ ] `%o`
- [ ] `%p`
- [ ] Width specifiers
- [ ] Precision
- [ ] Alignment
- [ ] Zero padding

---

## License

This project is released under the MIT License.
