## Example 1
```
// EXAMPLE1.math
a = 2^3 - floor(3.50)
b = 0.333 * a(5 - 1.2)
c = 4 / 3 + .5x
d = c mod 4 - 2
y = d ^ ( 1/3 ) * b
```
```
Tokens:
  a      VARIABLE
  =      EQUAL
  2      NUMBER
  ^      EXPONENT
  3      NUMBER
  -      MINUS
  floor  GENERIC_FUNC
  (      OPEN_PAREN
  3.50   NUMBER
  )      CLOSE_PAREN
  \n     ENDOFLINE
  b      VARIABLE
  =      EQUAL
  0.333  NUMBER
  *      MULTIPLY
  a      VARIABLE
  (      OPEN_PAREN
  5      NUMBER
  -      MINUS
  1.2    NUMBER
  )      CLOSE_PAREN
  \n     ENDOFLINE
  c      VARIABLE
  =      EQUAL
  4      NUMBER
  /      DIVIDE
  3      NUMBER
  +      PLUS
  .5     NUMBER
  x      VARIABLE
  \n     ENDOFLINE
  d      VARIABLE
  =      EQUAL
  c      VARIABLE
  mod    MOD
  4      NUMBER
  -      MINUS
  2      NUMBER
  \n     ENDOFLINE
  y      VARIABLE
  =      EQUAL
  d      VARIABLE
  ^      EXPONENT
  (      OPEN_PAREN
  1      NUMBER
  /      DIVIDE
  3      NUMBER
  )      CLOSE_PAREN
  *      MULTIPLY
  b      VARIABLE
```

## Example 2
```
// EXAMPLE2.math
f = log10.254(x^2)
p = (3.14159)^2
m = fp
c = 54.23/11.96
y = m + -x / 10 * c
```
```
Tokens:
  f      VARIABLE
  =      EQUAL
  log10  LOG
  (      OPEN_PAREN
  x      VARIABLE
  ^      EXPONENT
  2      NUMBER
  )      CLOSE_PAREN
  \n     ENDOFLINE
  p      VARIABLE
  =      EQUAL
  (      OPEN_PAREN
  3.14159        NUMBER
  )      CLOSE_PAREN
  ^      EXPONENT
  2      NUMBER
  \n     ENDOFLINE
  m      VARIABLE
  =      EQUAL
  f      VARIABLE
  p      VARIABLE
  \n     ENDOFLINE
  c      VARIABLE
  =      EQUAL
  54.23  NUMBER
  /      DIVIDE
  11.96  NUMBER
  \n     ENDOFLINE
  y      VARIABLE
  =      EQUAL
  m      VARIABLE
  +      PLUS
  -      MINUS
  x      VARIABLE
  /      DIVIDE
  10     NUMBER
  *      MULTIPLY
  c      VARIABLE
```

## Example 3

```
// EXAMPLE3.math
A = ceil(.5*x) * 0.2
a = x * (1 / 3)
B = sin(A * 66.666)
b = aB
y = b
```

```
Tokens:
  A      VARIABLE
  =      EQUAL
  ceil   GENERIC_FUNC
  (      OPEN_PAREN
  .5     NUMBER
  *      MULTIPLY
  x      VARIABLE
  )      CLOSE_PAREN
  *      MULTIPLY
  0.2    NUMBER
  \n     ENDOFLINE
  a      VARIABLE
  =      EQUAL
  x      VARIABLE
  *      MULTIPLY
  (      OPEN_PAREN
  1      NUMBER
  /      DIVIDE
  3      NUMBER
  )      CLOSE_PAREN
  \n     ENDOFLINE
  B      VARIABLE
  =      EQUAL
  sin    GENERIC_FUNC
  (      OPEN_PAREN
  A      VARIABLE
  *      MULTIPLY
  66.666         NUMBER
  )      CLOSE_PAREN
  \n     ENDOFLINE
  b      VARIABLE
  =      EQUAL
  a      VARIABLE
  B      VARIABLE
  \n     ENDOFLINE
  y      VARIABLE
  =      EQUAL
  b      VARIABLE
```