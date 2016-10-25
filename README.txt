Text-based adventure game; can you find enough magic rings and incriminating documents to indict and retire all the politicians before your HP runs out?

Zank home page: https://github.com/andy5995/Zank/wiki

Dependencies: libncurses (make and cmake optional to build)

On Windows, to build with cmake and MinGW, go to
/win32 in the Zank folder and type 'make'.

to build on Linux or Windows (if using MingGW)
gcc -Wall main.c functions.c -lncurses -o Zank

'make install' is not working yet.

e,w,n,s or cursor keys = direction keys
h = display in-game help
i = show inventory
m = display map
q = quit

When you are at position 0,0, you are at the bottom-left corner of the map.
When you are at position 9,9, you are in the top-right corner.

Inspiration for Zank came from BBS Door games such as Zork, Legend of the Red Dragon (L.O.R.D.), and Lunatix.

License: GNU GPL 3.0

Join the chat at https://gitter.im/Zank-dev/Lobby


This file last updated 2016-10-25
