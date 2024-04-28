#include "sudoku.h"

void printPuzzle(int puzzle[PUZZLE_SUURUS][PUZZLE_SUURUS], bool clear = true) {
    if (clear) {
        setCursorPosition(0, 0);
    }
    std::string text, separator, padding;
    separator = "+-------+-------+-------+";
    std::cout << separator << std::endl;

    for (int i = 0; i < PUZZLE_SUURUS; i++) {
        padding = "|       |       |       |";
        if (i != 0 && i % 3 == 0) {
            std::cout << separator << std::endl;
        }
        for (int j = 0; j < PUZZLE_SUURUS; j++) {
            if (j == 0) {
                std::cout << "| ";
            }
            std::string value = puzzle[i][j] == TYHI_VAL ? " " : std::to_string(puzzle[i][j]);
            std::cout << value << " ";
            if ((j + 1) % 3 == 0) {
                std::cout << "| ";
            }
        }
        std::cout << std::endl;
        if ((i + 1) % 3 == 0 || i == PUZZLE_SUURUS - 1) {
            std::cout << separator << std::endl;
        } else {
            std::cout << padding << std::endl;
        }
    }
}


bool isValid(int puzzle[PUZZLE_SUURUS][PUZZLE_SUURUS], int rida, int col, int vaart) {
    for (int c = 0; c < PUZZLE_SUURUS; c++) {
        if (puzzle[rida][c] == vaart) {
            return false;
            }
        }
    for (int r = 0; r < PUZZLE_SUURUS; r++) {
        if (puzzle[r][col] == vaart){
            return false;
            }
        }
    int startRow = floor(rida / 3) * 3, startCol = floor(col / 3) * 3;
    for (int r = startRow; r < startRow + 3; r++) {
        for (int c = startCol; c < startCol + 3; c++) {
            if (puzzle[r][c] == vaart) {
                return false;
                }
            }
        }
        return true;
    }

bool hasEmptyCell(int puzzle[PUZZLE_SUURUS][PUZZLE_SUURUS]) {
    for (int r = 0; r < PUZZLE_SUURUS; r++) {
        for (int c = 0; c < PUZZLE_SUURUS; c++) {
            if (puzzle[r][c] == TYHI_VAL) {return true;}
        }
    }
    return false;
}

void copyPuzzle(int origin[PUZZLE_SUURUS][PUZZLE_SUURUS], int (&copy)[PUZZLE_SUURUS][PUZZLE_SUURUS]) {
    for (int r = 0; r < PUZZLE_SUURUS; r++) {
        for (int c = 0; c < PUZZLE_SUURUS; c++) {
            copy[r][c] = origin[r][c];
        }
    }
}

bool fillPuzzle(int (&puzzle)[PUZZLE_SUURUS][PUZZLE_SUURUS]) {
    int rida, col;
    for (int i = 0; i < PUZZLE_SUURUS * PUZZLE_SUURUS; i++) {
        rida = floor(i / PUZZLE_SUURUS);
        col = i % PUZZLE_SUURUS;
        if (puzzle[rida][col] == TYHI_VAL) {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(values.begin(), values.end(), std::default_random_engine(seed));
            for (int j = 0; j < PUZZLE_SUURUS; j++) {
                if (isValid(puzzle, rida, col, values[j])) {
                    puzzle[rida][col] = values[j];
                    if (!hasEmptyCell(puzzle) || fillPuzzle(puzzle)) {
                        return true;
                    }
                }
            }
            break;
        }
    }
    puzzle[rida][col] = TYHI_VAL;
    return false;
}
