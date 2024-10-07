#pragma once
#include <array>
#include <iterator>
#include <memory>
#include <vector>

#include "constants.h"

struct Moves {
  std::array<int, 8> scores;

  Moves() { scores.fill(0); }

  int size() const { return scores.size(); }
  int at(int x) { return scores[x]; }
};

void calculate_move_scores(Board *board, Moves *moves);