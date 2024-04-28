#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <random>
#include <array>
#include <chrono>
#include <thread>

const int TYHI_VAL = 0;
const int PUZZLE_SUURUS = 9;
std::array<int, 9> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
int numberOfSolution = 1;

void printPuzzle(int puzzle[PUZZLE_SUURUS][PUZZLE_SUURUS], bool clear = true);
bool isValid(int puzzle[PUZZLE_SUURUS][PUZZLE_SUURUS], int rida, int col, int vaart);
bool hasEmptyCell(int puzzle[PUZZLE_SUURUS][PUZZLE_SUURUS]);
void copyPuzzle(int origin[PUZZLE_SUURUS][PUZZLE_SUURUS], int (&copy)[PUZZLE_SUURUS][PUZZLE_SUURUS]);
void generatePuzzle(int (&puzzle)[PUZZLE_SUURUS][PUZZLE_SUURUS], int difficulty = 1);

#endif
