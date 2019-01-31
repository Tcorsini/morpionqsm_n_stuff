/*
  Includes functions useful for most of board gales such as chess or connect4
 */
#ifndef RECTANGULAR_BOARD_FUN_HPP
#define RECTANGULAR_BOARD_FUN_HPP

#include "rectangular_board.hpp"
namespace timGames {
  template <enum direction8 D>
  int next_pos(const RectangularBoardAbstract& B, int id) {
    return B.adj_id(id, D);
  }
  
  //ligne potentielle maximale
  bool stop_max_line_size(int occur, const int& original_value, const int& current_value) {
    return (current_value != 0 && current_value != original_value);
    //|| occur > max_length);
  }

  //ligne potentielle limitée
  bool stop_no_max_line_size(int occur, const int& original_value, const int& current_value) {
    return (original_value != current_value);
  }
  /*int left_horizontal(const RectangularBoardAbstract& B, int id);
  int right_horizontal(const RectangularBoardAbstract& B, int id);
  int left_vertical(const RectangularBoardAbstract& B, int id);
  int right_vertical(const RectangularBoardAbstract& B, int id);
  int left_diag_dr(const RectangularBoardAbstract& B, int id);
  int right_diag_dr(const RectangularBoardAbstract& B, int id);
  int left_diag_ur(const RectangularBoardAbstract& B, int id);
  int right_diag_ur(const RectangularBoardAbstract& B, int id);
  //static int max_length = 0;
  //ligne potentielle maximale
  bool stop_max_line_size(int occur, const int& original_value, const int& current_value);
  //ligne potentielle limitée
  bool stop_no_max_line_size(int occur, const int& original_value, const int& current_value);*/
}

#endif
