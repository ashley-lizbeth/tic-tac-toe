#include <array>
#include <cctype>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <ostream>
#include <utility>
using namespace std;

const array<array<int, 3>, 3> INITIAL_CELL_SCORES = {3, 2, 3, 2, 4, 2, 3, 2, 3};

array<array<char, 3>, 3> board;
array<array<int, 3>, 3> cell_scores = INITIAL_CELL_SCORES;
array<int, 8> move_scores;

int move_count = 1;

const char ENEMY_TALLY = 'O', OWN_TALLY = 'X', NEUTRAL_TALLY = '|';
const int CELL_OCCUPIED = -100;

int get_cell_value(int col, int row) {
  char cell = board[col][row];
  if (cell == ENEMY_TALLY)
    return -1;
  if (cell == OWN_TALLY)
    return 1;
  return 0;
}

void update_move_scores() {
  move_scores.fill(0);

  for (int col = 0; col < 3; col++) {
    for (int row = 0; row < 3; row++) {
      int cell_value = get_cell_value(col, row);

      bool is_right_diagonal_cell = col == row;
      bool is_left_diagonal_cell = col + row == 2;

      if (is_right_diagonal_cell) {
        move_scores[6] += cell_value;
      }
      if (is_left_diagonal_cell) {
        move_scores[7] += cell_value;
      }

      move_scores[row] += cell_value;
      move_scores[3 + col] += cell_value;
    }
  }

  for (int s = 0; s < move_scores.size(); s++) {
    if (move_scores[s] == -2)
      move_scores[s] *= 2;
    if (move_scores[s] == 2)
      move_scores[s] *= 3;
  }
}

bool is_cell_occupied(int col, int row) {
  return board[col][row] != NEUTRAL_TALLY;
}

void update_cell_scores() {
  cell_scores = INITIAL_CELL_SCORES;
  array<int, 8> abs_move_scores;

  for (int i = 0; i < move_scores.size(); i++) {
    abs_move_scores[i] = abs(move_scores[i]);
  }

  for (int col = 0; col < 3; col++) {
    for (int row = 0; row < 3; row++) {
      if (is_cell_occupied(col, row)) {
        cell_scores[col][row] = CELL_OCCUPIED;
        continue;
      }

      bool is_right_diagonal_cell = col == row;
      bool is_left_diagonal_cell = col + row == 2;

      if (is_right_diagonal_cell) {
        cell_scores[col][row] += abs_move_scores[6];
      }

      if (is_left_diagonal_cell) {
        cell_scores[col][row] += abs_move_scores[7];
      }

      cell_scores[col][row] +=
          (abs_move_scores[row] + abs_move_scores[col + 3]);
    }
  }
}

pair<int, int> find_best_cell() {
  pair<pair<int, int>, int> best_score = {{0, 0}, -10};

  for (int col = 0; col < 3; col++) {
    for (int row = 0; row < 3; row++) {
      int score = cell_scores[col][row];

      if (score == CELL_OCCUPIED)
        continue;

      if (score > best_score.second)
        best_score = {{col, row}, score};
    }
  }

  return best_score.first;
}

pair<int, int> capture_enemy_move() {
  string enemy_move;
  cin >> enemy_move;
  int col, row;

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
    cout << "Invalid move\n";
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
    cout << "Invalid move\n";
    return {-1, -1};
  }

  if (board[col][row] == OWN_TALLY) {
    cout << "Space already ocupied\n";
    return {-1, -1};
  }

  return {col, row};
}

void print_board() {
  cout << "Move " << move_count++ << "\n";
  cout << "  1 2 3\n";
  for (int col = 0; col < board.size(); col++) {
    switch (col) {
    case 0:
      cout << "A ";
      break;
    case 1:
      cout << "B ";
      break;
    case 2:
      cout << "C ";
      break;
    }
    for (auto cell : board[col]) {
      cout << cell << " ";
    }
    cout << "\n";
  }
  cout << "\n";
}

bool has_anyone_won() {
  for (auto s : move_scores) {
    if (abs(s) == 3)
      return true;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(0);

  for (int i = 0; i < board.size(); i++) {
    board[i].fill(NEUTRAL_TALLY);
  }

  bool goes_first;
  string goes_first_string;

  cout << "Do you wish to go first? ";
  cin >> goes_first_string;

  goes_first = tolower(goes_first_string[0]) != 'y';

  cout << "\n";

  while (!has_anyone_won()) {
    if (goes_first) {
      pair<int, int> cell = find_best_cell();
      board[cell.first][cell.second] = OWN_TALLY;

      print_board();

      update_move_scores();
      if (has_anyone_won())
        break;
    }

    pair<int, int> enemy_cell = capture_enemy_move();

    if (enemy_cell == make_pair(-1, -1)) {
      goes_first = false;
      continue;
    }

    board[enemy_cell.first][enemy_cell.second] = ENEMY_TALLY;

    print_board();

    update_move_scores();
    update_cell_scores();

    goes_first = true;
  }
}