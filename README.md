# Brose

#### *Blue Rose*

A scripting language with a mathematical syntax.
Compiles to a object (an AST) which can be called with an input parameter (x) to return a value (y), just like a mathematical function/algorithm.

## Supported Languages
Brose currently only has support for *C++*.

## Setup

### Dependencies
- [Boost.Regex](https://github.com/boostorg/regex) (header-only)

### Prerequisites
- [Premake5](https://github.com/premake/premake-core)
- Your favorite build system

### Build
With GNU Make:
```
git clone https://github.com/acer-leon-dev/brose-lang
premake5 gmake
make
```
Or you can run premake with any other build system.

## Examples

[ex1.brose](docs\Examples\ex1.brose)
```
// ex1.brose
a = 2^3 - floor(3.50)
b = 0.333 * a(5 - 1.2)
c = 4 / 3 + .5x
d = c mod 4 - 2
y = d ^ ( 1/3 ) * b
```

[ex2.brose](docs\Examples\ex2.brose)
```
// ex2.brose
f = log10(x^2)
p = (3.14159)^2
m = fp
c = 54.23/11.96
y = m + -x / 10 * c
```

[ex3.brose](docs\Examples\ex3.brose)
```
// ex3.brose
A = ceil(.5*x) * 0.2
a = x * (1 / 3)
B = sin(A * 66.666)
b = aB
y = b
```