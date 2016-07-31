# Zank
Text (console/cli) game. Can you find enough magic rings and incriminating documents to indict and retire all the politicians before your HP runs out?

The windows .exe file is in the win32/ folder of the Zank archive.
It was built using MinGW on ReactOS 4.01 ( https://www.reactos.org/ ) and hasn't yet been fully tested.

On Windows, to build with cmake and MinGW, go to
/win32 in the Zank folder and type 'make'.

to build on Linux or Windows (if using MingGW)
gcc -Wall main.c functions.c -lncurses -o Zank

'make install' is not working yet.

i = show inventory

m = display map

q = quit

e,w,n,s or cursor keys = direction keys

When you are at position 0,0, you are at the bottom-left corner of the map.
When you are at position 9,9, you are in the top-right corner.

Inspiration for Zank came from games such as Zork, Legend of the Red Dragon (L.O.R.D.), and Lunatix.

License: GNU GPL 3.0

This file last updated 2016-07-30
