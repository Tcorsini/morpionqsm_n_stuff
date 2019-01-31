#include "rectangular_board_fun.hpp"

using namespace timGames;

int left_horizontal(const RectangularBoardAbstract& B, int id) {
  return B.adj_id(id, LEFT);
}
int right_horizontal(const RectangularBoardAbstract& B, int id) {
  return B.adj_id(id, RIGHT);
}
int left_vertical(const RectangularBoardAbstract& B, int id) {
  return B.adj_id(id, UP);
}
int right_vertical(const RectangularBoardAbstract& B, int id) {
  return B.adj_id(id, DOWN);
}
int left_diag_dr(const RectangularBoardAbstract& B, int id) {
  int id2 = B.adj_id(id, UP);
  if (id2 == -1)
    return -1;
  return B.adj_id(id2, LEFT);
}
int right_diag_dr(const RectangularBoardAbstract& B, int id) {
  int id2 = B.adj_id(id, DOWN);
  if (id2 == -1)
    return -1;
  return B.adj_id(id2, RIGHT);
}
int left_diag_ur(const RectangularBoardAbstract& B, int id) {
  int id2 = B.adj_id(id, DOWN);
  if (id2 == -1)
    return -1;
  return B.adj_id(id2, LEFT);
}
int right_diag_ur(const RectangularBoardAbstract& B, int id) {
  int id2 = B.adj_id(id, UP);
  if (id2 == -1)
    return -1;
  return B.adj_id(id2, RIGHT);
}
//static int max_length = 0;
//ligne potentielle maximale
bool stop_max_line_size(int occur, const int& original_value, const int& current_value) {
  return (current_value != 0 && current_value != original_value);
	  //|| occur > max_length);
}

//ligne potentielle limitée
bool stop_no_max_line_size(int occur, const int& original_value, const int& current_value) {
  return (original_value != current_value);
}
