# sudoku-cpp
Sudoku game. This project is developed using qt framework.

# Grid generating
Currently there is one generator that uses backtracking algorithm.

![alt text](https://github.com/pillon33/sudoku-cpp/blob/main/full_board.png?raw=true)

## Backtracking generator
It first fills diagonal sub-squares with random numbers and assures that each number occures only once in each sub-square (theres no other way to make a mistake in this step). This first step is a random element that ensures it will generate random boards and won't end up generating the same output each time. The second step uses backtracking algorithm to fill the board within sudoku rules. This algorithm checks each possibility, if given number meets sudoku rules it goes to next field, the number is increased otherwise. If all numbers result with mistake the field is left with 0 and algorithm goes to the previous field. 

# Mask generating
Next step to create a puzzle is to create a mask for fully filled board (leave empty fields). The algorithm should ensure that theres only one possible solution.

# Mistake checking
There are two algorithm for mistake checking, the first one iterates through whole grid and checks if there are any mistakes. The second one is optimised to check if last change was a mistake or not. They are only used while generating puzzle, then mistakes are checkd comparing correct solution with current board state.

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
