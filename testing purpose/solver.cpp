#include "sudoku.h"

void solveSudoku(int puzzle[PUZZLE_SUURUS][PUZZLE_SUURUS], bool visualize = false) {
    int rida, col;
    for (int i = 0; i < PUZZLE_SUURUS * PUZZLE_SUURUS; i++) {
        rida = floor(i / PUZZLE_SUURUS);
        col = i % PUZZLE_SUURUS;
        if (puzzle[rida][col] == TYHI_VAL) {
            for (int vaart = 1; vaart <= PUZZLE_SUURUS; vaart++) {
                if (isValid(puzzle, rida, col, vaart)) {
                    puzzle[rida][col] = vaart;
                    if (visualize) {
                        sleep(100);
                        printPuzzle(puzzle);
                    }
                    if (!hasEmptyCell(puzzle)) {
                        numberOfSolution++;
                        if (visualize) {
                            sleep(100);
                            printPuzzle(puzzle);
                            return true;
                        }
                        break;
                    }
                    else if (solveSudoku(puzzle, visualize)) {
                        return true;
                    }
                }
            }
            break;
        }
    }
    puzzle[rida][col] = TYHI_VAL;
    if (visualize) {
        sleep(100);
        printPuzzle(puzzle);
    }
    return false;
}
