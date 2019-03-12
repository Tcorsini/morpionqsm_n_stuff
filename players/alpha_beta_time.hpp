#ifndef ALPHA_BETA_TIME
#define ALPHA_BETA_TIME

#include "alpha_beta.hpp"

class AlphaBetaTime : public AlphaBeta {
public:
  AlphaBetaTime(int (*heuristique) (int, int, void*),
	    int (*moves_getter) (int**, int, void*),
	    void (*play) (int, int, void*),
	    void (*revert_play) (int, int, void*),
	    int (*next_player) (int, void*),
	    bool (*last_move) (int, void*));
  virtual ~AlphaBetaTime() {}
  long min_max_time(int depth, int player_id, void* obj,
		    double time, bool random=false);
  long alpha_beta_time(int depth, int player_id, void* obj, double time,
		  bool random = false, bool isAlphaBeta = true,
		  long alpha = MIN_HEURISTIQUE, long beta = MAX_HEURISTIQUE);
};

#endif
