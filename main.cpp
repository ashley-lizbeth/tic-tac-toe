#include <array>
#include <cctype>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <ostream>

#include "cell.h"
#include "constants.h"
#include "move_calculations.h"
#include "print_functions.h"

bool DEBUG_MODE = false;
int move_count = 1;

bool has_game_ended(CellScores *cell_scores, Moves *moves) {
  for (auto s : moves->scores) {
    if (abs(s) == 3)
      return true;
  }

  for (auto f : cell_scores->field) {
    for (auto cs : f)
      if (cs != CELL_OCCUPIED)
        return false;
  }

  return true;
}

bool player_turn(Board *board) {
  Coordinates enemy_cell = capture_and_translate_enemy_move(board);

  if (enemy_cell == Coordinates(-2, -2)) {
    DEBUG_MODE = !DEBUG_MODE;
    return false;
  }

  if (enemy_cell == Coordinates(-1, -1)) {
    return false;
  }

  board->field[enemy_cell.column][enemy_cell.row] = ENEMY_TALLY;

  print_board(board, move_count++);
  return true;
}

void machine_turn(Board *board, CellScores *cell_scores) {
  Coordinates cell = find_best_cell(cell_scores);
  board->field[cell.column][cell.row] = OWN_TALLY;

  print_board(board, move_count++);
}

int main() {
  std::ios_base::sync_with_stdio(0);

  Board board;
  CellScores cell_scores;
  Moves move_scores;

  bool does_machine_play = false;

  std::string goes_first_string;
  std::cout << "Do you wish to go first? ";
  std::cin >> goes_first_string;

  std::cout << std::endl;

  does_machine_play = tolower(goes_first_string[0]) != 'y';

  while (!has_game_ended(&cell_scores, &move_scores)) {
    if (does_machine_play) {
      machine_turn(&board, &cell_scores);
      does_machine_play = false;
    } else {
      does_machine_play = player_turn(&board);
    }

    calculate_move_scores(&board, &move_scores);
    update_cell_scores(&board, &cell_scores, &move_scores);

    if (DEBUG_MODE)
      print_debug_info(&cell_scores, &move_scores);
  }
}