# Mastermind
Implementation of the mastermind game in C

I decied to make this game because it seemed a fun game to program.
This version of the game allows the user to play Mastermind using mouse left click,
the user can select the color he/she wants to place and then the spot, the size of the 
board can go from 4 to 8 pieces.
There is an initial menu, a new game menu and a statistics menu where the user can watch the statistics for the games recorded in the file
When the user terminates the program, he/she reopening the program has the curent game saved and ready to keep playing


This program compiles using gcc with the following command:
gcc *.c -g -I/usr/local/include  -Wall -pedantic -std=c99 -L/usr/local/lib -lm -lSDL2 -lSDL2_ttf -lSDL2_image -o Mastermind

And it runs with:
./Mastermind

I included a compiled version so you don't have to install the SDL2 libraries and adds to be able to compile

01/08/2017
Gonçalo Mestre