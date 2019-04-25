[![CircleCI](https://circleci.com/gh/lucasgcb/CPython-Extensions.svg?style=svg)](https://circleci.com/gh/lucasgcb/CPython-Extensions)

### About

This repository contains an example project where C code wrapped and compiled through a setup script. 

This works based on the fact C code and routines may be run through Python through its implementation in [CPython, the reference interpreter of Python ("standard")](https://www.python.org/download/alternatives/).
### Why?

- Sometimes you have some effective **C code you want to interface** with something easier to work with and couple stuff to.

- Routines of compiled code in your Python scripts **increase performance**. Loops and other things within Python is extremely costly, not so much in C.

- This also gives you **free type checking** since the argument types are explicit.

### How?

[There is a C header file](https://github.com/python/cpython/blob/master/Include/Python.h) available through CPython that gives you the tools for the conversion of Python Objects into C data, letting you convert from and to Python Objects within C code for processing or whatever else. 

There is also a defined structure for defining modules and [this is well documented](https://docs.python.org/3/c-api/).

Here, I make two submodules to a main module called `pyextensions`: `lilterminal` and `mymath`.

- [`lilterminal`](./src/pyextensions/lilterminal.c) implements a tiny interface for using the command prompt using C's `system` function..
- [`mymath`](./src/pyextensions/mymath.c) implements a simple add operation, showing how to input multiple arguments into a function

### Instructions on this example

To install this example, go into the containing folder and run:
```
pip install . 
```

This will compile the C code, and install the implementations as submodules of the main `pyextensions` module. 

You can find the example in [examples](./example/main.py). 

### Resources

- [Getting started with Extensions](https://docs.python.org/3/extending/extending.html)
- [C-API reference documentation](https://docs.python.org/3/c-api/)
- [Matthew Drury's Blog Post on performance](http://madrury.github.io/jekyll/update/programming/2016/06/20/python-extension-modules.html)
