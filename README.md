*This project has been created as part of the 42 curriculum by lwicket.*

## ℹ️ Project Overview

`ft_printf` is one of the first projects at 42 School. It consists of reimplementing parts of the printf function in C, on top of nothing but the [`write(2)`](https://sites.uclouvain.be/SystInfo/manpages/man2/write.2.html) syscall.

"printf" stands for "print formatted". As the name implies, it's a function that formats text and outputs it.

The objective is to introduce students to the concept of variadic functions, but also to train their coding discipline and get them to write reusable code.

Amusingly enough, this project is either the easiest or the most challenging one students have to tackle at this point in the cursus, depending on whether they choose to handle the flags or not.

### Contents

The assignment mandates support for the following conversion specifiers: `%`, `c`, `s`, `p`, `i`, `u`, `d`, `x`, `X`.

For bonus points, the conversions must also handle all of the following flags: `-`, `+`, space, `0`, `#`. That is, all the standard flags.

## 🛠️ Build & Usage

### Requirements

- GCC or Clang
- [`ar`](https://en.wikipedia.org/wiki/Ar_(Unix)) for creating the archive
- [C99](https://en.cppreference.com/w/c/99.html) support
- A UNIX-like system (such as Linux or macOS)

As per the assignment, the code is compiled using `cc`. It is not specified which compiler `cc` refers to, but it is safe to assume that it will be either GCC or Clang.

### Building the static library

To build the project, simply run `make` from the project root:
```bash
make
```
This will produce a `libftprintf.a` archive containing my libft, extended with the ft_printf function this project is about.

### Compiling with libftprintf.a

```bash
cc <your src/obj files> libftprintf.a -I<path to the directory containing ft_printf.h>
```

> [!WARNING]
> `libftprintf.a` must come AFTER everything that uses it in the list of files you provide to the compiler. This is because the linker discards all the functions in your archive that aren't currently needed, and its list of necessary functions is based exclusively on the objects it has parsed so far. If `libftprintf.a` is the very first file provided in your link command, all of its contents will be discarded!

## 📋 Coding Style

My coding style conforms to the [Norm](./norm.en.pdf), a set of strict style guidelines enforced for all C exercises, which every student must follow under penalty of a zero grade.

Beyond purely cosmetic considerations, the Norm also forbids the following language constructs:

- `for` loops
- `do … while` loops
- `switch` statements
- `goto`
- the ternary operator
- declarations with initialization
- assignments inside controlling expressions

(non-exhaustive list)

> [!TIP]
> You can find the latest version of the Norm in the [Norminette repository](https://github.com/42School/norminette) – the program used to check conformity with the Norm. The version of the Norm included in this repository is the one that was in use when I completed this project.

## 🧑‍🔬 Implementation Notes

printf has a surprising amount of internal state that we need to keep track of. Since global variables are forbidden, the easiest way to do that is to store everything in a single structure that is passed down through the whole "printf pipeline". This structure is named the "context" (ctx for short), is allocated in ft_printf's stack frame, and contains data such as the current conversion specification, the output buffer, the variadic arguments, how many bytes have been written, and whether an error occurred.

What I call the printf pipeline consists of these three parts:

1. parsing
2. conversion
3. output

### 1. Parsing

The way printf should format its output is determined by a conversion specification, which follows this grammar:

```
%[flags][width][.precision][length]type
```
This information must be extracted from the format string and turned into data the code can use. This is the role of the parser.

The parser just goes through the format string and fills the context structure with the information it extracts.

The length modifiers looked like a pain in the ass to implement, and they aren't mandated by the assignment. My implementation just skips them.

### 2. Conversion

Conversion consists of transforming the values passed to printf as variadic arguments according to the specification. The most complicated part of conversion is handling the padding. This is mainly achieved through two functions, `put_padded` and `put_numeric`. `put_padded` receives the string to be printed and its length, and figures out how to pad it. Things like the precision can alter the padding, with slightly different rules depending on the type of the conversion (whether you convert a string, an int, or a char), so the caller of `put_padded` is responsible for computing the length of the string and modifying the flags if applicable.

Since the padding and precision rules are mostly the same for all numeric conversions (decimal, hexadecimal, etc.), the `put_numeric` function was introduced as a common interface to limit code duplication.

The numeric conversions themselves are performed by the `ft_jutoa` function from my Libft, which is exactly like an itoa function, except that it operates on `uintmax_t`.

> [!TIP]
> The `ju` prefix of `jutoa` comes from the printf format specifier for `uintmax_t`, which is `%ju`.

### 3. Output

The output is buffered, as printing character by character would involve so many syscalls that printf would just be unusable in any I/O-intensive project.

The buffer has a size of 4096 bytes, like in other popular libcs. As per the assignment, the buffer management of the original printf is NOT reproduced: the buffer is flushed when ft_printf returns (rather than at program exit) or when it is full. The buffering mode can't be changed by the user.

## 📚 References & Acknowledgments

### ISO/IEC 9899:2024 aka C23

This is the official document that defines the behavior required of conforming printf implementations. I used it as the authoritative reference for the behavior of every flag and conversion specifier.

You can purchase the Standard for the modest sum of 227 CHF on iso.org. Alternatively, you can download a free draft version that is 99% identical to the final version: https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf

### Wikipedia

https://en.wikipedia.org/wiki/Printf

### AI usage

As usual, AI was used to proofread my otherwise handcrafted README.
