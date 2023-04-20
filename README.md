# sudoku-cpp
Sudoku game. This project is developed using qt framework.

# Grid generating
Currently there are two generators.

![alt text](https://github.com/pillon33/sudoku-cpp/blob/main/full_board.png?raw=true)

## Backtracking generator
It first fills diagonal sub-squares with random numbers and assures that each number occures only once in each sub-square (theres no other way to make a mistake in this step). This first step is a random element that ensures it will generate random boards and won't end up generating the same output each time. The second step uses backtracking algorithm to fill the board within sudoku rules. This algorithm checks each possibility, if given number meets sudoku rules it goes to next field, the number is increased otherwise. If all numbers result with mistake the field is left with 0 and algorithm goes to the previous field. 

## Shuffle generator
This generator has much lower complexity because it doesn't need to solve puzzle to get filled board. It starts with filled board called pattern it can be any board that meets sudoku rules, I am using the simplest possible pattern. Then it does some transformations that don't affect rules. Technically result is still the same board as the pattern but because of these random transformations user can't see that it's the same board. Combining it with random mask generator makes it completly impossible to see that it's the same pattern. 

Transformations done to the pattern are:
 - shuffling digits,
 - randomly rearanging groups of rows within themselves,
 - randomly rearanging groups of columns within themselves,
 - randomly rearanging rows of sub-squares,
 - randomly rearanging columns of sub-squares.

 Default pattern:
 
 ![alt text](https://github.com/pillon33/sudoku-cpp/blob/main/default_pattern.png?raw=true)

# Mask generating
Mask generator creates random order to go through the grid, removes number from grid and uses backtracking algorithm to check if puzzle has only one solution, after finishing the loop it tries again if score isn't satisfying and hasn't reached max tries possible.

![alt text](https://github.com/pillon33/sudoku-cpp/blob/main/example_puzzle.png?raw=true)

# Mistake checking
There are two algorithm for mistake checking, the first one iterates through whole grid and checks if there are any mistakes. The second one is optimised to check if last change was a mistake or not. 

![alt text](https://github.com/pillon33/sudoku-cpp/blob/main/example_mistakes.png?raw=true)
