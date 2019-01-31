#include "rectangular_board.hpp"
#include <cstdio>

using namespace timGames;
//using namespace morpion;

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
/* Board :
   |0|1|2|3| line 0
   |4|5|6|7| line 1
   |8|9|10|11| line 2
*/
static enum direction8 d4_d8[4] = {N, E, S, W};
static enum direction4 d8_d4[4] = {UP, RIGHT, DOWN, LEFT};

enum direction8 timGames::dir4_to_dir8(enum direction4 d) {return d4_d8[d];}
enum direction4 timGames::dir8_to_dir4(enum direction8 d) {return d8_d4[d/2];}

int RectangularBoardAbstract::adj_id(int id, enum direction8 dir) const {
  int line = get_line(id);
  int col = get_column(id);
  switch(dir) {
  case N:
    line--;
    break;
  case NE:
    line--;
  case E:
    col++;
    break;
  case ES:
    col++;
  case S:
    line++;
    break;
  case SW:
    line++;
  case W:
    col--;
    break;
  case WN:
    col--;
    line--;
    break;
  }
  if (line >= lines || line < 0 || col < 0 || col >= columns)
    return -1;
  return calculate_pos_board(line, col);
}

int RectangularBoardAbstract::adj_id(int id, enum direction4 dir) const {
  return adj_id(id, dir4_to_dir8(dir));
}


/*int line = get_line(id);
  int col = get_column(id);
  switch(dir) {
  case UP:
    line--;
    break;
  case RIGHT:
    col++;
    break;
  case DOWN:
    line++;
    break;
  case LEFT:
    col--;
    break;
  }
  if (line >= lines || line < 0 || col < 0 || col >= columns)
    return -1;
  return calculate_pos_board(line, col);*/
