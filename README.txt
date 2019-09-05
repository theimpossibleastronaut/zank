# zank

Text-based adventure game; can you find enough magic rings and
incriminating documents to indict and retire all the politicians before
your HP runs out?

zank home page:<https://github.com/theimpossibleastronaut/zank/wiki>

screenshots:<https://github.com/theimpossibleastronaut/zank/tree/master/screenshots>

## Dependencies:

  * gcc
  * cmake
  * libncurses-dev
  * libjson-c <https://github.com/json-c/json-c>

zank will try to link against a local copy of libjson-c, which you can
get by cloning it as a submodule. While inside the zank repo:

    git submodule update --init --recursive

Then to build json-c:

    cd external/json-c
    ./autogen.sh
    ./configure --prefix=$PWD/local
    make
    make install

## Compiling

### Linux and Mac

    mkdir build
    cd build
    cmake ../source
    make

### Windows

    mkdir build
    cd build
    cmake -G "MinGW Makefiles" ..\source
    mingw32-make

The zank executable will be output to your build directory. To run, use

    ./zank

zank doesn't have need to be installed because it can be run as a
stand-alone binary. At present, all the data is built into the program.

e,w,n,s or cursor keys = direction keys
h = display in-game help
i = show inventory
m = display map
q = quit

Inspiration for zank came from BBS Door games such as Zork, Legend of
the Red Dragon (L.O.R.D.), and Lunatix.

License: GNU GPL 3.0

This file last updated 2018-11-23
