#include "connect4.hpp"
#include "rectangular_board_fun.hpp"
#include <cstdio>

using namespace timGames;

/*
int n; //lignes
int m; //colonnes
int l; //taille ligne
int *T; //tableau

int nb_piece; //nb pieces played
int *nb_pieces; //nb pieces in each column, optimization

int calculate_id_board(int line, int col) { return line * m + col; }
    inline int get_line(int id) { return id/m; }
    inline int get_column(int id) { return id % m; }
    int adj_id(int id, enum direction dir);
*/
/* Connect4 :
   |0|1|2|3| line 0
   |4|5|6|7| line 1
   |8|9|10|11| line 2
*/

int Connect4::linesize(int id,
		    int (*left) (const RectangularBoardAbstract&, int),
		    int (*right) (const RectangularBoardAbstract&, int),
		    bool max_line_size) const {
  if (!board.is_pos_valid(id))
    throw "the given position is not valid";
  int count = 1;
  bool (*stop) (int, const int&, const int&);
  if (max_line_size)
    stop = stop_max_line_size;
  else
    stop = stop_no_max_line_size;
  //max_length = length;
  //printf("%d\n", count);
  count += board.linesizeoneway(id, left, stop);
  //printf("%d\n", count);
  count += board.linesizeoneway(id, right, stop);
  //printf("%d-----------\n", count);
  //printf("count : %d", count);
  return count;
}

/*
int Connect4::nb_horizontal(int id, bool max_line_size) const {
  return linesize(id, next_pos<W>, next_pos<E>left_horizontal, right_horizontal, max_line_size);
}
int Connect4::nb_vertical(int id, bool max_line_size) const {
  return linesize(id, left_vertical, right_vertical, max_line_size);
}
int Connect4::nb_diag_dr(int id, bool max_line_size) const {
  return linesize(id, left_diag_dr, right_diag_dr, max_line_size);
}
int Connect4::nb_diag_ur(int id, bool max_line_size) const {
  return linesize(id, left_diag_ur, right_diag_ur, max_line_size);
}
 */

int Connect4::nb_horizontal(int id, bool max_line_size) const {
  return linesize(id, next_pos<W>, next_pos<E>, max_line_size);
}
int Connect4::nb_vertical(int id, bool max_line_size) const {
  return linesize(id, next_pos<N>, next_pos<S>, max_line_size);
}
int Connect4::nb_diag_dr(int id, bool max_line_size) const {
  return linesize(id, next_pos<WN>, next_pos<ES>, max_line_size);
}
int Connect4::nb_diag_ur(int id, bool max_line_size) const {
  return linesize(id, next_pos<SW>, next_pos<NE>, max_line_size);
}

//check if the piece gives the player a win
bool Connect4::check_winning_piece(int id) const {
  if (!board.is_pos_valid(id))
    return false;//throw "Invalid argument value in check_winning_piece";
  int player = board.get_piece(id);
  if (player == 0)
    return false;
  int line = nb_vertical(id);
  if (line >= length) return true;
  line = nb_horizontal(id);
  if (line >= length) return true;
  line = nb_diag_dr(id);
  if (line >= length) return true;
  line = nb_diag_ur(id);
  if (line >= length) return true;
  return false;
}


//play in the column, returns the id of the added piece, -1 otherwise
int Connect4::add_piece(int player, int column) {
  if (player <= 0 || !can_play(column))
    return -1;
  int id = board.calculate_pos_board((board.lines-1) - nb_pieces_columns[column]++, column);
  previous_moves[nb_piece++] = column; //column + n * (nb_pieces_columns[column]++);
  board.put_piece(id, player);
  //last_move = id;
  return id;
}

void Connect4::remove_piece(int column) {
  if (column < 0 || column >= board.columns
      || nb_pieces_columns[column] <= 0) {
    display_board();
    printf("Trying to remove in %d (should not happen)\n", column);
    throw;
  }
  int id = board.calculate_pos_board((board.lines-1)
				     - --nb_pieces_columns[column], column);
  nb_piece--;
  board[id] = 0;//.put_piece(id, 0);
}


bool Connect4::can_play(int column) const {
  if (column < 0 || column >= board.columns)
    return false;
  bool b1 = nb_pieces_columns[column] < board.lines;
  bool b2 = board.get_piece(column) == 0;
  if (b1 != b2) {
    printf("nb pieces : %d, column : %d, nb_pieces_columns[column] = %d\n",
	   nb_piece, column, nb_pieces_columns[column]);
    display_board();
    throw "tableau inconsistent";
  }
  return b1;
}

int Connect4::get_moves(int player_id, int** moves) const {
  (void) player_id;
  int x = 0;
  *moves = new int[board.columns];
  for(int i = 0; i < board.columns; i++)
    if (can_play(i)) {
      (*moves)[x++] = i;
    }
  return x;
}

//play in the column, return -1 if impossible, 0 or 1 if the player wins
int Connect4::play(int player, int column) {
  int id = add_piece(player, column);
  if (id < 0)
    return -1;
  if (check_winning_piece(id)) {
    //printf("Gagné ! Joueur %d !\n", player);
    return 1;
  }
  return 0;
}

int Connect4::game_status() const {
  if (nb_piece > 0) {
    int last_piece = get_id_col(get_last_move());
    if (check_winning_piece(last_piece))
      return board.get_piece(last_piece);
  }
  if (nb_piece >= board.table_size)
    return -1;
  return 0;
}

//red, yellow, green, blue
static int Colors[4] = {31, 33, 32, 34};

void Connect4::display_board() const {
  printf("\n");
  for(int i = 0; i < board.lines; i++) {
    for(int j = 0; j < board.columns; j++) {
      printf("|");
      int id = board.calculate_pos_board(i,j);
      int x = board.get_piece(id);//T[calculate_id_board(i,j)];
      if (x == 0)
	printf(" ");
      else
	printf("\x1b[%dm%d\x1b[0m", Colors[(x-1)%4], x);
    }
    printf("|\n");
  }
  printf("\n");
}

int Connect4::get_id_col(int column) const {
  return board.calculate_pos_board((board.lines-1) - (nb_pieces_columns[column] -1), column);
}

int Connect4::get_last_move() const {return previous_moves[nb_piece-1];}

int Connect4::get_last_pos() const {
  return get_id_col(get_last_move());
}
