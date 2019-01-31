#ifndef CHIFOUMI_HPP
#define CHIFOUMI_HPP

#include "game.hpp"

namespace timGames {
  namespace chifoumi {

    enum chifoumi_move {
      PIERRE = 0,
      FEUILLE = 1,
      CISEAUX = 2
    };

    class Chifoumi : public virtual Game {
    private:
      unsigned int victory_required;
      int players_status[2];
    public:

      virtual ~Chifoumi() {}
      
      Chifoumi(unsigned int victory_required = 1);

      virtual int get_moves(int player_id, void** moves);
      virtual int get_moves(int player_id, const enum chifoumi_move** moves);
      virtual void clean_moves(void** moves);
      virtual int game_status();
      virtual int play(int player_id, int move_id);
      virtual int revert_play() {return 1;};
      virtual bool is_move_valid(int player_id, int move_id);
      virtual void display_status();
    };

  }
}

#endif
