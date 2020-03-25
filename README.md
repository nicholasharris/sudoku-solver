# sudoku-solver
A simple C++ program that solves sudoku puzzles in terminal via recursive backtracking. Also uses some deduction tricks specific to sudoku puzzles to speed things up. Solves even the hardest puzzles in under 30 seconds (and easy puzzles in 1-2 seconds). Using only recursive backtracking the hardest of puzzles took approximately 6 hours to solve; I had to utilize specific deduction tricks used in sudoku puzzles to vastly increase the speed of the program.

The lack of a GUI interface means the program is tedious to use (entering all clue numbers through the command line takes quite a bit of time). But as an exercise I felt this project was rewarding.

This code was tested in Windows, using Microsoft Visual Studio 2015.

To use the program, first enter all the clue numbers in the format "row col number", with each value being between 1 and 9, inclusive. For example, entering "1 1 1", will place a clue number of 1 in the upper left hand corner of the puzzle. When all clue numbers are entered, enter "0 0 0" and the program will solve the puzzle, usually within a few seconds.

Picture of the command line interface: 

![alt text](https://raw.githubusercontent.com/nicholasharris/sudoku-solver/master/sudoku_solver_interface.png)
