
#ifndef CLASSIC_AI
#define CLASSIC_AI

#include "player.hpp"
#include "../games/connect4.hpp"
#include "alpha_beta.hpp"

namespace timGames {

  struct ClassicAI_fun {
    static int heuristique(int player_id, int depth, void* obj);
    static int moves_getter (int** moves, int player_id, void* obj);
    static void play (int player_id, int move, void* obj);
    static void revert_play(int player_id, int move, void* obj);
    static int next_player(int player_id, void* obj);
    static bool last_move(int player_id, void* obj);
  };

  class ClassicAI : virtual public Player {
    AlphaBeta core;
    Connect4 myboard;
    const char* name;
    int id;

    int depth;
    int n;
    int m;
    int l;
    int nb_players;
    int *score_players; //contains a value for each players (0 : p1, 1 : p2...)

    void calculateScore(int id, int player_id);
    void remove_piece(int column, int player_id);
  public:
    ClassicAI(int id, const char* name, int depth = 3, int line = 6,
	      int column = 7, int length = 4, int nb_players = 2);
    virtual ~ClassicAI();

    virtual int chooseMove(int player_id,
			   int nb_moves, int *moves);
    virtual void play(int player_id, int move_id);
    virtual void status();
    friend class ClassicAI_fun;
  };
  
}
#endif
