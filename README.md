# Brose

#### *Blue Rose*

A scripting language with a mathematical syntax.
Compiles to a C++ object (an AST) which can be called with an input parameter (x) to return a value (y), just like a mathematical function/algorithm.

## Setup

### Dependencies
- [Boost.Regex](https://github.com/boostorg/regex)

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

[EXAMPLE1.brose](docs\Examples\EXAMPLE1.brose)
```
// EXAMPLE1.brose
a = 2^3 - floor(3.50)
b = 0.333 * a(5 - 1.2)
c = 4 / 3 + .5x
d = c mod 4 - 2
y = d ^ ( 1/3 ) * b
```

[EXAMPLE2.brose](docs\Examples\EXAMPLE2.brose)
```
// EXAMPLE2.brose
f = log10(x^2)
p = (3.14159)^2
m = fp
c = 54.23/11.96
y = m + -x / 10 * c
```

[EXAMPLE3.brose](docs\Examples\EXAMPLE3.brose)
```
// EXAMPLE3.brose
A = ceil(.5*x) * 0.2
a = x * (1 / 3)
B = sin(A * 66.666)
b = aB
y = b
```
