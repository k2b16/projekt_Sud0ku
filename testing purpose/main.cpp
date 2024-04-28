#include "sudoku.h"

#include <Windows.h>
#include <thread>  

void setCursorPosition(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hOut, coord);
}
void sleep(int milliseconds) {std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));}

void newGame(int (&puzzle)[PUZZLE_SUURUS][PUZZLE_SUURUS]) {
    int difficulty;
    std::cout << "Select difficulty level:\n";
    std::cout << "1. Easy\n";
    std::cout << "2. Medium\n";
    std::cout << "3. Hard\n";
    std::cin >> difficulty;

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
        std::cout << "Select an option:\n";
        std::cout << "1. Solve puzzle\n";
        std::cout << "2. New game\n";
        std::cout << "3. Clear console\n";
        std::cout << "4. Exit\n";

        std::cin >> choice;

        if (choice == "1") {
            newGame(puzzle);
            copyPuzzle(puzzle, origin);
            solveSudoku(puzzle, true);
            //printPuzzle(origin, false);
        } else if (choice == "2") {
            newGame(puzzle);
            copyPuzzle(puzzle, origin);
        } else if (choice == "3") {
            clearConsole();
        } else if (choice == "4") {
            break;
        } else if (choice == "5") {
            std::cout << "Hello world!" << std::endl;
            break; 
        } else {std::cout << "Invalid choice. Please select again.\n";}
    }

    return 0;
}
