# sudoku-cpp
Sudoku game. This project is developed using qt framework.

# Grid generating
Currently there is one generator that uses backtracking algorithm.

## Backtracking generator
It first fills diagonal sub-squares with random numbers and assures that each number occures only once in each sub-square (theres no other way to make a mistake in this step). This first step is a random element that ensures it will generate random boards and won't end up generating the same output each time. The second step uses backtracking algorithm to fill the board within sudoku rules. This algorithm checks each possibility, if given number meets sudoku rules it goes to next field, the number is increased otherwise. If all numbers result with mistake the field is left with 0 and algorithm goes to the previous field. 

# TODO
UI:
  - General layout :heavy_check_mark:
  - 9x9 Board :x:
  - Marking corresponding numbers on board :x:

Game logic:
  - Generate puzzle :x:
  - Check for mistakes in square :x:
  - Check for mistakes in row/column :x:
  - Check if solved :x:
  - Timer :x:
  - Statistics :x:
  
Game settings:
  - Show / hide mistakes :x:
  - Difficulty level :x:
