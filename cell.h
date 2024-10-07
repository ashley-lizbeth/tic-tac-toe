#pragma once
#include "constants.h"
#include "move_calculations.h"

const std::array<std::array<int, 3>, 3> INITIAL_CELL_SCORES = {3, 2, 3, 2, 4,
                                                               2, 3, 2, 3};

struct CellScores {
  std::array<std::array<int, 3>, 3> field;

  CellScores() : field(INITIAL_CELL_SCORES){};

  char at(Coordinates coords) { return field.at(coords.column).at(coords.row); }

  void reset() { field = INITIAL_CELL_SCORES; }
};

bool is_cell_occupied(Board *board, int col, int row);

Coordinates find_best_cell(CellScores *cell_scores);

void update_cell_scores(Board *board, CellScores *cell_scores,
                        Moves *move_scores);