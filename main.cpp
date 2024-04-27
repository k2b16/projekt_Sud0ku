#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <random>
#include <array>
#include <chrono>
#include <thread>
#include <Windows.h>

const int EMPTY_VALUE = 0;
const int PUZZLE_SIZE = 9;
std::array<int, 9> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
int numberOfSolution = 1;

void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hOut, coord);
}

void sleep(int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void printPuzzle(int puzzle[PUZZLE_SIZE][PUZZLE_SIZE], bool clear = true)
{
    if (clear)
    {
        setCursorPosition(0, 0);
    }
    std::string text, separator, padding;

    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        text = "|";
        separator = " -";
        padding = "|";
        for (int j = 0; j < PUZZLE_SIZE; j++)
        {
            std::string value = puzzle[i][j] == EMPTY_VALUE ? " " : std::to_string(puzzle[i][j]);
            text += "  " + value + "  |";
            separator += "------";
            padding += "     |";
            if (j % 3 == 2 && j != PUZZLE_SIZE - 1)
            {
                text += "|";
                padding += "|";
            }
        }
        if (i != 0 && i % 3 == 0)
        {
            std::replace(separator.begin(), separator.end(), '-', '=');
        }
        std::cout << separator << std::endl;
        std::cout << padding << std::endl;
        std::cout << text << std::endl;
        std::cout << padding << std::endl;
    }
    std::cout << separator << std::endl;
}

bool isValid(int puzzle[PUZZLE_SIZE][PUZZLE_SIZE], int row, int col, int value)
{
    for (int c = 0; c < PUZZLE_SIZE; c++)
    {
        if (puzzle[row][c] == value)
            return false;
    }
    for (int r = 0; r < PUZZLE_SIZE; r++)
    {
        if (puzzle[r][col] == value)
            return false;
    }
    int startRow = floor(row / 3) * 3, startCol = floor(col / 3) * 3;
    for (int r = startRow; r < startRow + 3; r++)
    {
        for (int c = startCol; c < startCol + 3; c++)
        {
            if (puzzle[r][c] == value)
                return false;
        }
    }
    return true;
}

bool hasEmptyCell(int puzzle[PUZZLE_SIZE][PUZZLE_SIZE])
{
    for (int r = 0; r < PUZZLE_SIZE; r++)
    {
        for (int c = 0; c < PUZZLE_SIZE; c++)
        {
            if (puzzle[r][c] == EMPTY_VALUE)
                return true;
        }
    }
    return false;
}

void copyPuzzle(int origin[PUZZLE_SIZE][PUZZLE_SIZE], int (&copy)[PUZZLE_SIZE][PUZZLE_SIZE])
{
    for (int r = 0; r < PUZZLE_SIZE; r++)
    {
        for (int c = 0; c < PUZZLE_SIZE; c++)
        {
            copy[r][c] = origin[r][c];
        }
    }
}

bool fillPuzzle(int (&puzzle)[PUZZLE_SIZE][PUZZLE_SIZE])
{
    int row, col;
    for (int i = 0; i < PUZZLE_SIZE * PUZZLE_SIZE; i++)
    {
        row = floor(i / PUZZLE_SIZE);
        col = i % PUZZLE_SIZE;
        if (puzzle[row][col] == EMPTY_VALUE)
        {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(values.begin(), values.end(), std::default_random_engine(seed));
            for (int j = 0; j < PUZZLE_SIZE; j++)
            {
                if (isValid(puzzle, row, col, values[j]))
                {
                    puzzle[row][col] = values[j];
                    if (!hasEmptyCell(puzzle) || fillPuzzle(puzzle))
                    {
                        return true;
                    }
                }
            }
            break;
        }
    }
    puzzle[row][col] = EMPTY_VALUE;
    return false;
}

bool solveSudoku(int puzzle[PUZZLE_SIZE][PUZZLE_SIZE], bool visualize = false)
{
    int row, col;
    for (int i = 0; i < PUZZLE_SIZE * PUZZLE_SIZE; i++)
    {
        row = floor(i / PUZZLE_SIZE);
        col = i % PUZZLE_SIZE;
        if (puzzle[row][col] == EMPTY_VALUE)
        {
            for (int value = 1; value <= PUZZLE_SIZE; value++)
            {
                if (isValid(puzzle, row, col, value))
                {
                    puzzle[row][col] = value;
                    if (visualize)
                    {
                        sleep(100);
                        printPuzzle(puzzle);
                    }
                    if (!hasEmptyCell(puzzle))
                    {
                        numberOfSolution++;
                        if (visualize)
                        {
                            sleep(100);
                            printPuzzle(puzzle);
                            return true;
                        }
                        break;
                    }
                    else if (solveSudoku(puzzle, visualize))
                    {
                        return true;
                    }
                }
            }
            break;
        }
    }
    puzzle[row][col] = EMPTY_VALUE;
    if (visualize)
    {
        sleep(100);
        printPuzzle(puzzle);
    }
    return false;
}

void generatePuzzle(int (&puzzle)[PUZZLE_SIZE][PUZZLE_SIZE], int difficulty = 1)
{
    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        for (int j = 0; j < PUZZLE_SIZE; j++)
        {
            puzzle[i][j] = EMPTY_VALUE;
        }
    }
    fillPuzzle(puzzle);
    srand((unsigned)time(0));
    int attempt = difficulty;
    while (attempt > 0)
    {
        int row = floor(rand() % PUZZLE_SIZE);
        int col = floor(rand() % PUZZLE_SIZE);
        while (puzzle[row][col] == EMPTY_VALUE)
        {
            row = floor(rand() % PUZZLE_SIZE);
            col = floor(rand() % PUZZLE_SIZE);
        }
        int backupValue = puzzle[row][col];
        puzzle[row][col] = EMPTY_VALUE;
        numberOfSolution = 0;
        solveSudoku(puzzle);
        if (numberOfSolution != 1)
        {
            puzzle[row][col] = backupValue;
            attempt--;
        }
    }
}

void newGame(int (&puzzle)[PUZZLE_SIZE][PUZZLE_SIZE])
{
    generatePuzzle(puzzle);
    system("cls");
    printPuzzle(puzzle);
}

void clearConsole()
{
    system("cls");
}

int main(int, char **)
{
    int puzzle[PUZZLE_SIZE][PUZZLE_SIZE];
    int origin[PUZZLE_SIZE][PUZZLE_SIZE];
    std::string choice;

    while (true)
    {
        std::cout << "Select an option:\n";
        std::cout << "1. Solve puzzle\n";
        std::cout << "2. New game\n";
        std::cout << "3. Clear console\n";
        std::cout << "4. Exit\n";

        std::cin >> choice;

        if (choice == "1")
        {
            solveSudoku(puzzle, true);
            printPuzzle(origin, false);
        }
        else if (choice == "2")
        {
            newGame(puzzle);
            copyPuzzle(puzzle, origin);
        }
        else if (choice == "3")
        {
            clearConsole();
        }
        else if (choice == "4")
        {
            break;
        }
        else if (choice == "5")
        {
            std::cout << "Hello world!" << std::endl;
            break; 
        }
        else
        {
            std::cout << "Invalid choice. Please select again.\n";
        }
    }

    return 0;
}
