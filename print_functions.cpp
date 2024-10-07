#include <iostream>
#include <ostream>
#include <string>

#include "print_functions.h"

Coordinates capture_and_translate_enemy_move(Board *board) {
  std::cout << "Your move: ";

  std::string enemy_move;
  std::cin >> enemy_move;
  int col, row;

  std::cout << std::endl;

  if (enemy_move == "debug") {
    return {-2, -2};
  }

  switch (toupper(enemy_move[0])) {
  case 'A':
    col = 0;
    break;
  case 'B':
    col = 1;
    break;
  case 'C':
    col = 2;
    break;
  default:
    std::cout << "Invalid move\n";
    return {-1, -1};
  }

  switch (enemy_move[1]) {
  case '1':
    row = 0;
    break;
  case '2':
    row = 1;
    break;
  case '3':
    row = 2;
    break;
  default:
    std::cout << "Invalid move\n";
    return {-1, -1};
  }

  if (board->field[col][row] == OWN_TALLY) {
    std::cout << "Space already ocupied\n";
    return {-1, -1};
  }

  return {col, row};
}

void print_board(Board *board, int move_count) {
  std::cout << "Move " << move_count << "\n";
  std::cout << "  1 2 3\n";
  for (int col = 0; col < board->field.size(); col++) {
    switch (col) {
    case 0:
      std::cout << "A ";
      break;
    case 1:
      std::cout << "B ";
      break;
    case 2:
      std::cout << "C ";
      break;
    }

    for (auto cell : board->field[col]) {
      std::cout << cell << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void print_debug_info(CellScores *cell_scores, Moves *move_scores) {
  std::cout << "Move scores: ";
  for (auto ms : move_scores->scores) {
    std::cout << ms << " ";
  }
  std::cout << std::endl << "\nCell scores: " << std::endl;
  for (auto f : cell_scores->field) {
    for (auto cs : f) {
      std::cout << cs << " ";
    }
    std::cout << std::endl;
  }
}