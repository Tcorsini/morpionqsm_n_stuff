#include "alpha_beta_time.hpp"

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
	     int time, bool random=false);

long AlphaBetaTime::
alpha_beta_time(int depth, int player_id, void* obj, int time,
		bool random = false, bool isAlphaBeta = true,
		long alpha = MIN_HEURISTIQUE, long beta = MAX_HEURISTIQUE);
