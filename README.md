# brose

#### *Blue Rose*

A scripting language with a mathematical syntax.
Compiles to a object (an AST) which can be called with an input parameter (x) to return a value (y), just like a mathematical function/algorithm.

## Supported Languages
Brose, as of now, only has support for C++.

## Setup

### Dependencies
- [Boost.Regex](https://github.com/boostorg/regex) (header-only)

### Prerequisites
- [Premake5](https://github.com/premake/premake-core)
- Your favorite build system

### Config
*Note: Run `premake5 --help` for a list of supported build systems and configuration settings.*
```
git clone https://github.com/acer-leon-dev/brose-lang
premake5 <buildsystem>
```
Then build with your chosen build system.
<br>*Note: brose has only been tested with GCC/MinGW on Windows.*

## Examples

Example scripts with the `.brose` file extension can be found in [Docs/Examples](Docs/Examples).
