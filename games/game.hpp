#ifndef GAME_HPP
#define GAME_HPP

namespace timGames {

class Game {
private:
  /*
    removes the last move played
   */
  virtual int revert_play()=0;
public:
  virtual ~Game() {}
  /*
    Given the player of id player_id, gives all the moves 
    possible for that player
   */
  virtual int get_moves(int player_id, void** moves)=0;
  /*
    Used to free the moves given to the player
   */
  virtual void clean_moves(void* moves)=0;
  /*
    Return the id of the winning player ([1,n])
    if the game is not over, return 0
    if there is no winner, return -1
   */
  virtual int game_status() const=0;
  /*
    Play the move, returns game_status
    if the move is not allowed, return -1 
    (need to check with my own interface)
   */
  virtual int play(int player_id, int move_id)=0;
  /*
    Given a move with the id x, 
    checks if the move is allowed for the given player
   */
  virtual bool is_move_valid(int player_id, int move_id) const=0;
};

}

#endif
