#ifndef CONNECT4_HPP
#define CONNECT4_HPP

#include "rectangular_board.hpp"
#include "game.hpp"

namespace timGames {
  
  class Connect4 : virtual public Game {
  private:
    int *previous_moves;
    RectangularBoard<int> board;
  protected:
    int length; //taille ligne

    int nb_piece; //nb pieces played
    int *nb_pieces_columns; //nb pieces in each column, optimization

    int linesize(int id, int (*left) (const RectangularBoardAbstract&, int),
		 int (*right) (const RectangularBoardAbstract&, int),
		 bool max_line_size = false) const;
    bool check_winning_piece(int id) const; //check if the piece gives the player a win
    
  public:
    int add_piece(int player, int column); //play in the column, returns the id of the added piece, -1 otherwise
    int nb_horizontal(int id, bool max_line_size = false) const; //12
    int nb_vertical(int id, bool max_line_size = false) const; //|
    int nb_diag_dr(int id, bool max_line_size = false) const; //¹2
    int nb_diag_ur(int id, bool max_line_size = false) const; //1²
    int get_last_move() const;
    int get_last_pos() const;
    //removes the last piece added in the column, useful for simulation, AI or debug 
    void remove_piece(int column);
    int get_id_col(int col) const;
    
    Connect4(int n = 6, int m = 7, int l = 4):
      board(n, m, 0), length(l), nb_piece(0)
    {
      if (l < 0 || (l > n && l > m))
	throw "invalid argument value";
      nb_pieces_columns = new int[m];
      for (int i = 0; i < m; i++)
	nb_pieces_columns[i] = 0;
      previous_moves = new int[n*m];
    }
    virtual ~Connect4() {
      delete[] nb_pieces_columns;
      delete[] previous_moves;
    }
    inline int get_max_line() const { return board.get_max_line(); }
    inline int get_max_column() const { return board.get_max_column(); }
    inline int get_max_length() const { return length; }
    inline int get_nb_pieces() const { return nb_piece; }
    //play in the column, return -1 if impossible, 0 or 1 if the player wins
    int play(int player, int column);
    void display_board() const;
    //check if a player has won and return its id, return 0 if the game shall continue, return -1 if no moves are available (the game is a null match)
    int game_status() const;
    bool can_play(int column) const;
    bool is_move_valid(int player_id, int move_id) const { return can_play(move_id);}

    //will create a table in moves and return its size of the possible moves
    //the moves will be allocated with new[], it must be destroyed by the user!
    int get_moves(int player_id, int** moves) const;
    int get_moves(int player_id, void** moves) { return get_moves(player_id, (int**) moves); }
    int revert_play() { remove_piece(get_last_move()); return 0; }
    void clean_moves(void* moves) const {delete[] (int*) moves;};
    void clean_moves(void* moves) {delete[] (int*) moves;};
  };
}
#endif
