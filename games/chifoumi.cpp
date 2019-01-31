#include "chifoumi.hpp"
#include <cstdlib>

using namespace timGames;
using namespace chifoumi;

const static enum timGames::chifoumi::chifoumi_move chifoumi_moves[3] = {PIERRE, FEUILLE, CISEAUX};

Chifoumi::Chifoumi(unsigned int victory_required): 
  victory_required(victory_required) 
{
  players_status[0] = 0;
  players_status[1] = 0;
}

int Chifoumi::get_moves(int player_id, void** moves) {
  return 1;
}

void Chifoumi::clean_moves(void** moves) {
  if (*moves == chifoumi_moves || moves == NULL)
    return;
  delete[] moves;
}

int Chifoumi::get_moves(int player_id, const enum chifoumi_move** moves) {
  return 1;
}

int Chifoumi::game_status() {
  return 1;
}
int Chifoumi::play(int player_id, int move_id) {
  return 0;
}
bool Chifoumi::is_move_valid(int player_id, int move_id) {
  return true;
}
void Chifoumi::display_status() {}
