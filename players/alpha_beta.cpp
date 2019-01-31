#include "alpha_beta.hpp"
#include <cstdio>
#include <cstdlib>
#include <time.h>

AlphaBeta::AlphaBeta(int (*heuristique) (int, int, void*),
		     int (*moves_getter) (int**, int, void*),
		     void (*play) (int, int, void*),
		     void (*revert_play) (int, int, void*),
		     int (*next_player) (int, void*),
		     bool (*last_move) (int, void*)):
  heuristique(heuristique),
  moves_getter(moves_getter),
  play(play),
  revert_play(revert_play),
  next_player(next_player),
  last_move(last_move)
{
  srand(time(NULL));
}

int sign(int x) {
  if (x < 0)
    return -1;
  return 1; //return x + sign(x)*depth;
}

long AlphaBeta::min_max(int depth, int player_id, void* obj, bool random) {
  return alpha_beta(depth, player_id, obj, random, false);
}

/*{
  if (depth <= 0 || last_move(player_id, obj)) {
    int x = heuristique(player_id, depth, obj);
    return x;
  }
  int* moves;
  int nb_moves = moves_getter(&moves, player_id, obj);
  int best_value = MIN_HEURISTIQUE;
  int best_move = DEFAULT_MOVE;
  for(int i = 0; i < nb_moves; i++) {
    int current_move = moves[i];
    play(player_id, current_move, obj);
    int value = -min_max(depth - 1, next_player(player_id, obj), obj);
    if (value >= best_value || (value == best_value && rand()%2 == 0)) {
      best_value = value;
      best_move = current_move;
    }
    revert_play(player_id, current_move, obj);
  }
  if (moves != NULL)
    delete[] moves;
  _best_move = best_move;
  return best_value;
  }*/

long AlphaBeta::alpha_beta(int depth, int player_id, void* obj, bool random,
			   bool isAlphaBeta, long alpha, long beta) {
  if (depth <= 0 || last_move(player_id, obj)) {
    int x = heuristique(player_id, depth, obj);
    return x;
  }
  int* moves;
  int nb_moves = moves_getter(&moves, player_id, obj);
  long best_value = MIN_HEURISTIQUE; //min_max
  int best_move = DEFAULT_MOVE;
  int i;
  for(i = 0;
      i < nb_moves && (!isAlphaBeta || alpha < beta || (random && alpha == beta));
      i++) {
    int current_move = moves[i];
    play(player_id, current_move, obj);
    long value = -alpha_beta(depth - 1, next_player(player_id, obj), obj,
			     random, isAlphaBeta, -beta, -alpha);
    if ((value > best_value) || (random && value == value && rand()%2 == 0)) {
      best_value = value; //best_value
      best_move = current_move;
    }
    if (isAlphaBeta && best_value > alpha)
      alpha = best_value;
    revert_play(player_id, current_move, obj);
  }
  _best_move = best_move;
  if (moves != NULL)
    delete[] moves;
  return best_value;
}
