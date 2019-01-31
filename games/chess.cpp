#include "chess.hpp"
#include "rectangular_board_fun.hpp"
#include <cstdio>

using namespace timGames;
using namespace chess;
using namespace std;
/*
enum ChessType {
  KING = 0, //1
  QUEEN,   //1
  ROOKS,   //2 //tower
  BISHOPS, //2 //fou
  KNIGHTS, //2 //knights
  PAWNS, //8
  NONE
};
  
struct ChessPiece {
  int player_id;
  enum ChessType type;
  int pos_id; //-1 : out of the board

  int *possible_moves;
  int moves_size;
  bool is_in_game() const {}
  void display() const;
  void calculate_moves(Chess& c);
      
  ChessPiece(int pid, enum ChessType type, int pos) {}
  int get_moves(const int** moves) {}
};

struct ChessMove {
  int player_id;
  enum ChessType my_piece; //rock : my_piece = NONE
  int old_pos; //rock : my king
  int new_pos; //rock : my tower
  enum ChessType enemy_piece;
    
  ChessMove(int move_id = 0);
  int to_int() const;
  bool is_valid(Chess& c);
};
  
struct ChessPlayer {
  int id;
  struct ChessPiece* pieces[MAX_PIECES];

  ChessPlayer(int pid);
      
  inline const struct ChessPiece* get_king() const {}
  bool king_is_threatened() const;
  int get_moves(int **moves) const;
};
  
class Chess : virtual public Game {
private:
  int *previous_moves;
  RectangularBoard<ChessPiece*> board;
  ChessPlayer players[2];

  int apply_move(struct ChessMove& move);
      
  //protected:
public:
  inline bool is_king_threatened(int pid) const {}
      
  int get_last_move() const;
  int revert_move(int move_id);
    
  Chess();
  virtual ~Chess() {}
  //play the move id, return -1 if impossible, 0 or 1 if the player wins
  int play(int player, int move_id);
  void display_board() const;
  //check if a player has won and return its id, return 0 if the game shall continue, return -1 if no moves are available (the game is a null match)
  int game_status() const;
  bool is_move_valid(int player_id, int move_id) const;
};
*/




//int player_id;
//enum ChessType type;
//int pos_id; //-1 : out of the board
const static int Colors[4] = {31, 33, 32, 34};
const static char names[NONE] = {'K', 'Q', 'f', 'c', 't', 'p'};
char chess_to_char(enum ChessType t) {
  return names[t];
}

void ChessPiece::display() const {
  printf("\x1b[%dm%c\x1b[0m", Colors[(player_id-1)%4], chess_to_char(type));
}

bool can_attack(const ChessPiece& atk, const ChessPiece& def,
		const RectangularBoardAbstract& board) {
  int posA = atk.pos_id;
  int posB = def.pos_id;
  
  int yA = board.get_line(posA);
  int xA = board.get_column(posA);
  int yB = board.get_line(posB);
  int xB = board.get_column(posB);

  int difX = xA - xB;
  int difY = yA - yB;
  switch (atk.type) {
  case KING:
    if ((difX <= 1 && difX >= -1) &&
	(difY <= 1 && difY >= -1))
      return true;
    break;
  case QUEEN:
    if (xA == xB || yA == yB)
      return true;
  case BISHOP:
    if ((difX ==  difY) ||
	(difX == -difY))
      return true;
    break;
  case KNIGHT:
    if (((difX == 2 || difX == -2) && (difY == -1 || difY == 1)) ||
	((difX == 1 || difX == -1) && (difY == -2 || difY == 2)))
      return true;
    break;
  case ROOK:
    if (xA == xB || yA == yB)
      return true;
    break;
  case PAWN:
    if ((difX == 1 || difX == -1) &&
	(difY == 1 || difY == -1)) //depend du joueur
      return true;
  default:
    break;
  }
  return false;
}

bool ChessPiece::is_threatened(const Chess& c) const {
  if (check_for_horses(c))
    return true;
  const ChessPiece** neighbours = NULL;
  int n = get_surrounding8(c, &neighbours);
  for(int i = 0; i < n; i++) {
    if (neighbours[i]->player_id != player_id &&
	((type != KING && c.is_move_valid(neighbours[i]->player_id ,ChessMove(neighbours[i]->player_id, neighbours[i]->type, neighbours[i]->pos_id, pos_id, type).to_int()))
	 || (type == KING &&
	     (can_attack(*(neighbours[i]), *this, c.board)))))
      {
      delete[] neighbours;
      return true;
      }
  }
  if (neighbours != NULL)
    delete[] neighbours;
  return false;
}

int ChessPiece::get_surrounding8(const Chess& c, const ChessPiece*** pieces) const {}
bool ChessPiece::check_for_horses(const Chess& c) const {}

void ChessPiece::calculate_moves(Chess& c) {
  if (possible_moves != NULL)
    delete[] possible_moves;
  
}

ChessPiece::ChessPiece(int pid, enum ChessType type, int pos):
  player_id(pid), type(type), pos_id(pos), possible_moves(NULL), moves_size(0)
{}

ChessPiece::~ChessPiece() {
  if (possible_moves != NULL)
    delete[] possible_moves;
}

void ChessMove::calculate_new_moves(Chess& c) {
  
}

ChessMove::ChessMove(int pid, enum ChessType my_piece, int opos,
	  int npos, enum ChessType enemy):
  opposite(false), player_id(pid), my_piece(my_piece), old_pos(opos),
  new_pos(npos), enemy_piece(enemy) {
}

ChessMove::ChessMove(int move_id) {
  opposite = false;
  if (move_id <= 0) {
    player_id = 0;
    my_piece = NONE;
    old_pos = -1;
    new_pos = -1;
    enemy_piece = NONE;
  }
  enemy_piece = (enum ChessType)((move_id%10)%(NONE+1));
  new_pos = (move_id/10)%100;
  old_pos = (move_id/1000)%100;
  my_piece = (enum ChessType)(((move_id/100000)%10)%(NONE+1));
  player_id = move_id/1000000;
}

int ChessMove::to_int() const {
  int value = player_id;
  value = value*10 + my_piece;
  value = value*100 + old_pos;
  value = value*100 + new_pos;
  value = value*10 + enemy_piece;
  return value;
}

struct ChessMove ChessMove::opposite_move() {
  ChessMove copy = *this;
  copy.opposite = true;
  copy.player_id = (player_id%NB_CHESS_PLAYERS + 1);
  copy.old_pos = this->new_pos;
  copy.new_pos = this->old_pos;
  return copy;
}

bool ChessMove::is_valid(Chess& c) {
  return c.try_move(*this);
}

ChessPlayer::ChessPlayer(int pid): id(pid) {
  for (int i = 0; i < MAX_PIECES; i++)
    pieces[i] = NULL;
}
bool ChessPlayer::king_is_threatened() const {
  const struct ChessPiece* myKing = get_king();
  return true;
}
int ChessPlayer::get_moves(int **moves) const {
  return 1;
}
struct ChessPiece* ChessPlayer::get_unused_piece(enum ChessType type) {
  for(int i = 0; i < MAX_PIECES; i++)
    if(pieces[i]->type == type &&
       !(pieces[i]->is_in_game()))
      return pieces[i];
  return NULL;
}

/*
int player_id;
enum ChessType my_piece; //rock : my_piece = NONE
int old_pos; //rock : my king
int new_pos; //rock : my tower
enum ChessType enemy_piece;*/
int Chess::apply_move(struct ChessMove& move) {
  if (!move.opposite &&
      !is_move_valid(move.player_id, move.to_int()))
    return -1;
  ChessPiece* enemy = board[move.new_pos];
  ChessPiece* me = board[move.old_pos];
  if (enemy != NULL)
    enemy->pos_id = -1;
  board[move.new_pos] = me;
  me->pos_id = move.new_pos;
  board[move.old_pos] = NULL;
  if (move.opposite) {//on recupere le pion depuis le "cimetierre" du joueur id
    enemy = players[move.player_id - 1].get_unused_piece(move.enemy_piece);
    board[move.old_pos] = enemy;
    enemy->pos_id = move.old_pos;
    //enemy->calculate_moves(*this);
  }
  //me->calculate_moves(*this);
  return 0;
}  

bool Chess::try_move(struct ChessMove& move) {
  apply_move(move);
  bool check = true;
  if (is_king_threatened(move.player_id))
    check = false;
  revert_move(move.to_int());
  return check;
}

int Chess::get_last_move() const {
  return previous_moves.back();
}

int Chess::revert_move(int move_id) {
  struct ChessMove opp_move = ChessMove(move_id).opposite_move();
  return apply_move(opp_move);
}

int Chess::revert_play() {
  int last_move = get_last_move();
  previous_moves.pop_back();
  int test = revert_move(last_move);
  
  struct ChessMove opp_move = ChessMove(last_move).opposite_move();
  opp_move.calculate_new_moves(*this);
  
  return test;
}

//play the move id, return -1 if impossible, 0 or 1 if the player wins
int Chess::play(int player, int move_id) {
  ChessMove move(move_id);
  if(apply_move(move) < 0)
    return -1;
  previous_moves.push_back(move_id);
  move.calculate_new_moves(*this);
  if (game_status() == player)
    return 1;
  return 0;
}

Chess::Chess(): board(CHESS_LINES, CHESS_COLUMNS, NULL) { //, players{1,2}
  int LONG_DIST = 8*7;
  int SHORT_DIST = 8*5;
  for(int i = 0; i < NB_CHESS_PLAYERS; i++) {
    players[i] = ChessPlayer(i+1);
    int king_pos = 3 + i*LONG_DIST;
    all_pieces[i*MAX_PIECES] = ChessPiece(i+1, KING, king_pos);
    all_pieces[i*MAX_PIECES+1] = ChessPiece(i+1, QUEEN, king_pos+1);
    
    for(int j = 0; j < 3; j++ ) {
      enum ChessType k = (enum ChessType)(j + BISHOP);//%(NONE);
      all_pieces[i*MAX_PIECES+2+j*2] = ChessPiece(i+1, k, king_pos - (j+1));
      all_pieces[i*MAX_PIECES+2+j*2+1] = ChessPiece(i+1, k, king_pos + (j+2));
    }
    for(int j = 0; j < CHESS_COLUMNS; j++)
      all_pieces[i*MAX_PIECES+ CHESS_COLUMNS + j] =
	ChessPiece(i+1, PAWN, CHESS_LINES + j + i*SHORT_DIST);

    for(int j = 0; j < MAX_PIECES; j++) {
      struct ChessPiece* p = all_pieces + i*MAX_PIECES + j;
      players[i].pieces[j] = p;
      board[p->pos_id] = p;
    }
  }
}

void Chess::display_board() const {
  printf("\n");
  for(int i = 0; i < board.lines; i++) {
    for(int j = 0; j < board.columns; j++) {
      printf("|");
      int id = board.calculate_pos_board(i,j);
      ChessPiece* x = board.get_piece(id);//T[calculate_id_board(i,j)];
      if (x == NULL)
	printf(" ");
      else
	x->display();
    }
    printf("|\n");
  }
  printf("\n");
}

//check if a player has won and return its id, return 0 if the game shall continue, return -1 if no moves are available (the game is a null match)
int Chess::game_status() const {
  int *moves = NULL;
  for (int id = 1; id <= NB_CHESS_PLAYERS; id++) {
    int nb_moves = get_moves(id, &moves);
    clean_moves(moves);
    if (nb_moves == 0) {
      if (is_king_threatened(id))
	return (id%NB_CHESS_PLAYERS + 1);
      return -1; //a voir si on met id
    }
  }
  return 0;
}

bool Chess::is_move_valid(int player_id, int move_id) const {
  int *possible_moves = NULL;
  int n = get_moves(player_id, &possible_moves);
  if (possible_moves != NULL) {
    for(int i = 0; i < n; i++)
      if (move_id == possible_moves[i]) {
	delete[] possible_moves;
	return true;
      }
    delete[] possible_moves;
  }
  return false;
}

int main() {
  Chess x;
  x.display_board();
  return 0;
}
