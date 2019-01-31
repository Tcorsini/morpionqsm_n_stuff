#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player {
public:
  virtual ~Player() {}
  //given the current situation, tries to find the best move for the player_id (to be used with itself generaly), moves represent the moves available
  virtual int chooseMove(int player_id,
			 int nb_moves, int *moves)=0;
  //will add to its perception of the game the current move
  virtual void play(int player_id, int move_id)=0;
  //debug
  virtual void status()=0;
};

#endif
