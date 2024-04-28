#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <random>
#include <array>
#include <chrono>
#include <thread>
#include <Windows.h>

const int TYHI_VAL = 0;
const int PUZZLE_SUURUS = 9;
std::array<int, 9> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
int numberOfSolution = 1;

void setCursorPosition(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hOut, coord);
}
void sleep(int milliseconds) {std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));}

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

bool solveSudoku(int puzzle[PUZZLE_SUURUS][PUZZLE_SUURUS], bool visualize = false) {
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

void generatePuzzle(int (&puzzle)[PUZZLE_SUURUS][PUZZLE_SUURUS], int difficulty = 1) {
    for (int i = 0; i < PUZZLE_SUURUS; i++) {
        for (int j = 0; j < PUZZLE_SUURUS; j++) {
            puzzle[i][j] = TYHI_VAL;
        }
    }
    fillPuzzle(puzzle);

    int cellsToRemove = 0;
    switch (difficulty) {
        case 1:
            cellsToRemove = 40;
            break;
        case 2:
            cellsToRemove = 50;
            break;
        case 3:
            cellsToRemove = 60;
            break;
        default:
            cellsToRemove = 40;
            break;
    }

    srand((unsigned)time(0));
    while (cellsToRemove > 0) {
        int row = floor(rand() % PUZZLE_SUURUS);
        int col = floor(rand() % PUZZLE_SUURUS);
        if (puzzle[row][col] != TYHI_VAL) {
            puzzle[row][col] = TYHI_VAL;
            cellsToRemove--;
        }
    }
}

void newGame(int (&puzzle)[PUZZLE_SUURUS][PUZZLE_SUURUS]) {
    std::string choice;
    while (true) {
        std::cout << "Valik:\n";
        std::cout << "1. Uus mang\n";
        std::cout << "2. Exit\n";
        std::cin >> choice;
        if (choice == "1") {
            break;
        } else if (choice == "2") {
            exit(0);
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    int difficulty;
    while (true) {
        std::cout << "Vali raskustase:\n";
        std::cout << "1. Lihtne\n";
        std::cout << "2. Keskmine\n";
        std::cout << "3. Raske\n";
        std::cin >> difficulty;
        if (difficulty >= 1 && difficulty <= 3) {
            break;
        } else {
            std::cout << "Invalid difficulty level.\n";
        }
    }

    generatePuzzle(puzzle, difficulty);
    system("cls");
    printPuzzle(puzzle);
}

void clearConsole() {system("cls");}

int main(int, char **) {
    int puzzle[PUZZLE_SUURUS][PUZZLE_SUURUS];
    int origin[PUZZLE_SUURUS][PUZZLE_SUURUS];
    std::string choice;

    while (true) {
        newGame(puzzle);
        copyPuzzle(puzzle, origin);

        while (true) {
            std::cout << "Valik:\n";
            std::cout << "1. Sisesta number\n";
            std::cout << "2. Lahenda\n";
            std::cout << "3. Exit\n";
            std::cin >> choice;

            if (choice == "1") {
                int row, col, value;
                std::cout << "Mis rida (1-9): ";
                std::cin >> row;
                std::cout << "Mis veerg (1-9): ";
                std::cin >> col;
                std::cout << "Mis number (1-9): ";
                std::cin >> value;

                if (row >= 1 && row <= 9 && col >= 1 && col <= 9 && value >= 1 && value <= 9) {
                    if (origin[row - 1][col - 1] == TYHI_VAL) {
                        puzzle[row - 1][col - 1] = value;
                        system("cls");
                        printPuzzle(puzzle);
                    } else {
                        std::cout << "Ei saa muuta.\n";
                    }
                } else {
                    std::cout << "Invalid input.\n";
                }
            } else if (choice == "2") {
                copyPuzzle(origin, puzzle);
                solveSudoku(puzzle, true);
            } else if (choice == "3") {
                break;
            } else {
                std::cout << "Invalid choice.\n";
            }
        }

        std::cout << "Soovite uuesti mängida? (ja/ei)\n";
        std::cin >> choice;
        if (choice != "ja") {
            break;
        }
    }

    return 0;
}
