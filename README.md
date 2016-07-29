# Zank
Text (console/cli) game. Can you find enough magic rings and incriminating documents to indict and retire all the politicians before your HP runs out?

To build: gcc -Wall main.c functions.c -lncurses -o Zank

(Working on option to build with cmake)

i = show inventory

m = display map

q = quit

e,w,n,s = direction keys

When you are at position 0,0, you are at the bottom-left corner of the map.
When you are at position 9,9, you are in the top-right corner.

Inspiration for Zank came from games such as Zork, Legend of the Red Dragon (L.O.R.D.), and Lunatix.

License: GNU GPL 3.0

This file last updated 2016-07-29
