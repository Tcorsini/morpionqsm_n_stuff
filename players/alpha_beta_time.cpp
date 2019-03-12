#include "alpha_beta_time.hpp"
#include <ctime>
#include <cstdio>

AlphaBetaTime::
AlphaBetaTime(int (*heuristique) (int, int, void*),
	      int (*moves_getter) (int**, int, void*),
	      void (*play) (int, int, void*),
	      void (*revert_play) (int, int, void*),
	      int (*next_player) (int, void*),
	      bool (*last_move) (int, void*)):
  AlphaBeta(heuristique, moves_getter, play,
	    revert_play, next_player, last_move)
{
}

long AlphaBetaTime::
min_max_time(int depth, int player_id, void* obj,
	     double time, bool random) {
  return alpha_beta_time(depth, player_id, obj, time, random, false);
}

long AlphaBetaTime::
alpha_beta_time(int depth, int player_id, void* obj, double time,
		bool random, bool isAlphaBeta,
		long alpha, long beta) {
  //struct timeval tv1, tv2;
  clock_t start, end;
  double delta;
  long result;
  int i = 1;
  start = clock();
  do {
    result = alpha_beta(i, player_id, obj, random, isAlphaBeta, alpha, beta);
    end = clock();
    delta = (double(end - start) / CLOCKS_PER_SEC);
    printf("depth : %d, time : %f\n", i, delta);
  } while (i++ < depth &&  delta < time);
  return result;
}
