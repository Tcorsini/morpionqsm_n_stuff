#ifndef CHESS_HPP
#define CHESS_HPP

#define CHESS_LINES 8
#define CHESS_COLUMNS 8
#define MAX_PIECES 16
#define NB_CHESS_PLAYERS 2

#include "rectangular_board.hpp"
#include "game.hpp"
#include <vector>

namespace timGames {
  namespace chess {
    
    struct Chess;
    
    struct ChessPosition {
      int line;
      int column;

      void display();
    };
  
    enum ChessType {
      KING = 0, //1
      QUEEN,   //1
      BISHOP, //2 //fou
      KNIGHT, //2 //knights
      ROOK,   //2 //tower
      PAWN, //8
      NONE
    };
  
    struct ChessPiece {
      int player_id;
      enum ChessType type;
      int pos_id; //-1 : out of the board

      int *possible_moves;
      int moves_size;
      inline bool is_in_game() const {return pos_id >= 0;};
      void display() const;
      void calculate_moves(Chess& c);
      bool is_threatened(const Chess& c) const;
      int get_surrounding8(const Chess& c, const ChessPiece***) const;
      bool check_for_horses(const Chess& c) const;
      
      ChessPiece(int pid = 0, enum ChessType type = NONE, int pos = -1);
          
      int get_moves(const int** moves) const {
	*moves = possible_moves;
	return moves_size;
      }
      
      virtual ~ChessPiece();
    };

    struct ChessMove {
      bool opposite;
      int player_id;
      enum ChessType my_piece; //rock : my_piece = NONE
      int old_pos; //rock : my king
      int new_pos; //rock : my tower
      enum ChessType enemy_piece;

      //must be called if the move was applied,
      //it will call for the surrounding pieces a new calculation
      void calculate_new_moves(Chess& c);
      ChessMove(int move_id = 0);
      ChessMove(int pid, enum ChessType my_piece, int opos,
		int npos, enum ChessType enemy);
      int to_int() const;
      bool is_valid(Chess& c);
      struct ChessMove opposite_move();
    };
  
    struct ChessPlayer {
      int id;
      struct ChessPiece* pieces[MAX_PIECES];

      ChessPlayer(int pid = 0);
      virtual ~ChessPlayer() {}
      
      inline const struct ChessPiece* get_king() const {return pieces[0];}
      struct ChessPiece* get_unused_piece(enum ChessType type);
      bool king_is_threatened() const;
      int get_moves(int **moves) const;
    };
  
    class Chess : virtual public Game {
      friend class ChessMove;
      friend class ChessPiece;
    private:
      struct ChessPiece all_pieces[MAX_PIECES*NB_CHESS_PLAYERS];
      std::vector<int> previous_moves;
      RectangularBoard<ChessPiece*> board;
      ChessPlayer players[NB_CHESS_PLAYERS];

      int apply_move(struct ChessMove& move);
      bool try_move(struct ChessMove& move);
      //bool check_move(struct ChessMove& move);
      //protected:
    public:
      inline bool is_king_threatened(int pid) const {
	return players[pid-1].king_is_threatened();
      }
      
      int get_last_move() const;
      int revert_move(int move_id);
    
      Chess();
      virtual ~Chess() {}
      //play the move id, return -1 if impossible, 0 or 1 if the player wins
      int play(int player, int move_id);
      void display_board() const;
      //check if a player has won and return its id, return 0 if the game shall continue, return -1 if no moves are available (the game is a null match)
      int game_status() const;

      bool try_move(int pid, int move_id) {
	ChessMove c(move_id);
	return try_move(c);
      }
      bool is_move_valid(int player_id, int move_id) const;

      //will create a table in moves and return its size of the possible moves
      //the moves will be allocated with new[], it must be destroyed by the user!
      int get_moves(int pid, int** moves) const {
	return players[pid-1].get_moves(moves);
      }
      int get_moves(int player_id, void** moves) {
	return get_moves(player_id, (int**) moves);
      }
      int revert_play();
      void clean_moves(void* moves) const {delete[] (int*) moves;};
      void clean_moves(void* moves) {delete[] (int*) moves;};
    };
  }
}


#endif
