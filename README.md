Langton's Ant
=============

A short project I whipped up one night, experimenting with a "cellular automaton" called [Langton's Ant](https://en.wikipedia.org/wiki/Langton's_ant).

Compiles with [clang](http://clang.llvm.org/).

The program outputs a PNG file using the [lodepng](https://github.com/lvandeve/lodepng) library.

The executable takes two arguments:
* a sequence of letters that specify what movement the ant should take (eg. RLR or LLRR to name a few)
* a number of movements (the program seems to bog down around 10^9 movements)

Interesting example
-------------------
```
langtons_ant LRRRRRLLR 10000000
```
