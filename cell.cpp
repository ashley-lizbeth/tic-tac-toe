#include "cell.h"

bool is_cell_occupied(Board *board, Coordinates coords) {
  return board->at(coords) != NEUTRAL_TALLY;
}

void update_cell_scores(Board *board, CellScores *cell_scores,
                        Moves *move_scores) {
  cell_scores->reset();
  Moves absolute_move_scores = *move_scores;

  for (int i = 0; i < absolute_move_scores.size(); i++) {
    absolute_move_scores.scores[i] = abs(absolute_move_scores.scores[i]);
  }

  for (int col = 0; col < 3; col++) {
    for (int row = 0; row < 3; row++) {
      if (is_cell_occupied(board, {col, row})) {
        cell_scores->field[col][row] = CELL_OCCUPIED;
        continue;
      }

      bool is_right_diagonal_cell = col == row;
      bool is_left_diagonal_cell = col + row == 2;

      if (is_right_diagonal_cell) {
        cell_scores->field[col][row] += absolute_move_scores.scores[6];
      }

      if (is_left_diagonal_cell) {
        cell_scores->field[col][row] += absolute_move_scores.scores[7];
      }

      cell_scores->field[col][row] += (absolute_move_scores.scores[row] +
                                       absolute_move_scores.scores[col + 3]);
    }
  }
}

Coordinates find_best_cell(CellScores *cell_scores) {
  std::pair<Coordinates, int> best_score = {{0, 0}, -10};

  for (int col = 0; col < 3; col++) {
    for (int row = 0; row < 3; row++) {
      int score = cell_scores->at({col, row});

      if (score == CELL_OCCUPIED)
        continue;

      if (score > best_score.second)
        best_score = {{col, row}, score};
    }
  }

  return best_score.first;
}