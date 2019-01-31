#include "human.hpp"
#include <cstdio>

int Human::chooseMove(int player_id, int nb_moves, int *moves) {
  int i = -1;
  if (nb_moves <= 0 || moves == NULL)
    throw "No moves available";
  printf("Please enter your move as player %d (%d possibilities) in :\n[",
	 id, nb_moves);
  printf("%d", moves[0]);
  for(int j = 1; j < nb_moves; j++)
    printf(", %d", moves[j]);
  printf("]\n");
  scanf("%d", &i);
  return i;
}

void Human::status() {
  printf("Player n°%d: Human %s\n", id, name);
}
