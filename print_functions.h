#pragma once
#include "cell.h"
#include "constants.h"
#include "move_calculations.h"

Coordinates capture_and_translate_enemy_move(Board *board);

void print_board(Board *board, int move_count);

void print_debug_info(CellScores *cell_scores, Moves *move_scores);
