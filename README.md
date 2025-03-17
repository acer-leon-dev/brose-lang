# Brose

#### *Blue Rose.*

A scripting language with a mathematical syntax that compiles to a C++ object which can be called with an input parameter to return a value that corresponds with the function outlined in the script.

## Setup

### Dependencies
- [Boost.Regex 7.0.1](https://github.com/boostorg/regex)

### Prerequisites
- [Premake5](https://github.com/premake/premake-core)

```
git clone https://github.com/acer-leon-dev/math-lang
premake5 gmake
make
```
Or use any other build system

## Examples

### [EXAMPLE1.math](docs\Examples\EXAMPLE1.math)
```
// EXAMPLE1.math
a = 2^3 - floor(3.50)
b = 0.333 * a(5 - 1.2)
c = 4 / 3 + .5x
d = c mod 4 - 2
y = d ^ ( 1/3 ) * b
```

### [EXAMPLE2.math](docs\Examples\EXAMPLE2.math)
```
// EXAMPLE2.math
f = log10(x^2)
p = (3.14159)^2
m = fp
c = 54.23/11.96
y = m + -x / 10 * c
```

### [EXAMPLE3.math](docs\Examples\EXAMPLE3.math)
```
// EXAMPLE3.math
A = ceil(.5*x) * 0.2
a = x * (1 / 3)
B = sin(A * 66.666)
b = aB
y = b
```