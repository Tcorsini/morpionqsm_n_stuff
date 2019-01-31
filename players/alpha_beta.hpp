#ifndef ALPHA_BETA
#define ALPHA_BETA

#include <limits.h>
#define MAX_HEURISTIQUE INT_MAX
#define MIN_HEURISTIQUE -MAX_HEURISTIQUE
#define DEFAULT_MOVE -1

#define DEPTH_MAX 100
//on évitera d'appeler alpha beta avec une profondeur inférieure à depth_max

/*
  MIN_HEURISTIQUE && MAX_HEURISTIQUE ne doivent pas être atteintes !
  toute valeur <= MIN_HEURISTIQUE ou >= MAX_HEURISTIQUE retournée
  par heuristique entraine un comportement indéterminé !
 */

class AlphaBeta {
protected:
  int (*heuristique) (int player_id, int depth, void* obj);
  int (*moves_getter) (int** moves, int player_id, void* obj);
  void (*play) (int player_id, int move, void* obj);
  void (*revert_play) (int player_id, int move, void* obj);
  int (*next_player) (int player_id, void* obj);
  bool (*last_move) (int player_id, void* obj);
public:
  int _best_move;
  AlphaBeta(int (*heuristique) (int, int, void*),
	    int (*moves_getter) (int**, int, void*),
	    void (*play) (int, int, void*),
	    void (*revert_play) (int, int, void*),
	    int (*next_player) (int, void*),
	    bool (*last_move) (int, void*));
  virtual ~AlphaBeta() {}
  //return the id of the best move
  long min_max(int depth, int player_id, void* obj, bool random=false);
  long alpha_beta(int depth, int player_id, void* obj,
		  bool random = false, bool isAlphaBeta = true,
		  long alpha = MIN_HEURISTIQUE, long beta = MAX_HEURISTIQUE);
};

#endif
