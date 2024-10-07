#include "move_calculations.h"
/*
In a game of tic-tac-toe, there are 8 possible winning moves:
    Filling one of the three rows
    Filling one of the three columns
    Filling one of the two diagonals

This file calculates the progress towards fulfilling any possibility each turn
*/

int get_cell_value(Board *board, Coordinates coords) {
  char cell = board->at(coords);

  if (cell == ENEMY_TALLY)
    return -1;

  if (cell == OWN_TALLY)
    return 1;

  return 0;
}

void boost_almost_wins(Moves *moves) {
  for (int i = 0; i < moves->size(); i++) {
    int *score = &(moves->scores[i]);
    if (*score == -2)
      *score *= 2;
    if (*score == 2)
      *score *= 3;
  }
}

void calculate_move_scores(Board *board, Moves *moves) {
  moves->reset();

  for (int col = 0; col < 3; col++) {
    for (int row = 0; row < 3; row++) {
      int cell_value = get_cell_value(board, {col, row});

      bool is_right_diagonal_cell = col == row;
      bool is_left_diagonal_cell = col + row == 2;

      if (is_right_diagonal_cell) {
        moves->scores[6] += cell_value;
      }
      if (is_left_diagonal_cell) {
        moves->scores[7] += cell_value;
      }

      moves->scores[row] += cell_value;
      moves->scores[3 + col] += cell_value;
    }
  }

  boost_almost_wins(moves);
}