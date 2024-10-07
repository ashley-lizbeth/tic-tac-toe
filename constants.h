#pragma once
#include <array>

const char ENEMY_TALLY = 'O', OWN_TALLY = 'X', NEUTRAL_TALLY = '|';
const int CELL_OCCUPIED = -100;

struct Coordinates {
  int column, row;

  Coordinates(int x, int y) {
    column = x;
    row = y;
  };

  bool operator==(Coordinates coords) {
    return coords.column == this->column && coords.row == this->row;
  }
};

struct Board {
  std::array<std::array<char, 3>, 3> field;

  char at(Coordinates coords) { return field.at(coords.column).at(coords.row); }

  Board() {
    for (int i = 0; i < field.size(); i++) {
      field[i].fill(NEUTRAL_TALLY);
    }
  }
};