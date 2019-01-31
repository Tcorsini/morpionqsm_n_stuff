#include "random_player.hpp"
#include <cstdio>
#include <cstdlib>
#include <time.h>

RandomPlayer::RandomPlayer(int player_id, const char* name):
  id(player_id), name(name)
{
  srand(time(NULL));
}

int RandomPlayer::chooseMove(int player_id, int nb_moves, int *moves) {
  int i = rand() % nb_moves;
  return moves[i];
}

void RandomPlayer::status() {
  printf("Player n°%d: Random %s\n", id, name);
}
