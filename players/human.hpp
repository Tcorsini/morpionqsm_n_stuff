#ifndef HUMAN_HPP
#define HUMAN_HPP
#include "player.hpp"

class Human : virtual public Player {
  int id;
  const char* name;
public:
  Human(int player_id, const char* name): id(player_id), name(name) {}
  virtual ~Human() {}
  //given the current situation, tries to find the best move for the player_id (to be used with itself generaly)
  virtual int chooseMove(int player_id, int nb_moves, int *moves);
  //will add to its perception of the game the current move
  virtual void play(int player_id, int move_id) {};
  virtual void status();
};

#endif
