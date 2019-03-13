#include "classic_ai.hpp"
#include <cstdio>

//temps en secondes
#define AI_TIME 1

namespace timGames {

  static int countPlay = 0;
  static int countReversePlay = 0;
  
  int ClassicAI_fun::heuristique (int player_id, int depth, void* obj) {
    ClassicAI* me = (ClassicAI*) obj;
    int board_status = me->myboard.game_status();
    int i;
    int score = 0;
    int depth_reductor = -1 - DEPTH_MAX + depth;
    if (depth_reductor > -1) depth_reductor = -1;
    switch(board_status) {
    case 0:
      for(i = 0; i < me->nb_players; i++) {
	if (i == player_id -1)
	  score += me->score_players[i];
	else
	  score -= me->score_players[i];
      }
      break;
    case -1:
      score = MIN_HEURISTIQUE/2 - depth;
      break;
    default:
      if (board_status == player_id)
	score = MAX_HEURISTIQUE + depth_reductor;
      else
	score = MIN_HEURISTIQUE - depth_reductor;
    }
    return score;
  }
  
  int ClassicAI_fun::moves_getter (int** moves, int player_id, void* obj) {
    (void) player_id;
    ClassicAI* me = (ClassicAI*) obj;
    return me->myboard.get_moves(player_id, moves);
  }
  
  void ClassicAI_fun::play (int player_id, int move, void* obj) {
    countPlay++;
    ClassicAI* me = (ClassicAI*) obj;
    me->myboard.play(player_id, move);
    int moveId = me->myboard.get_id_col(move);
    me->calculateScore(moveId, player_id);
  }
  
  void ClassicAI_fun::revert_play (int player_id, int move, void* obj) {
    countReversePlay++;;
    //(void) player_id;
    //printf("Revert play %d\n", move);
    ClassicAI* me = (ClassicAI*) obj;
    //me->myboard.revert_play();
    me->remove_piece(move, player_id);
  }
  
  int ClassicAI_fun::next_player (int player_id, void* obj) {
    ClassicAI* me = (ClassicAI*) obj;
    return 1 + player_id % me->nb_players;
  }
  
  bool ClassicAI_fun::last_move (int player_id, void* obj) {
    (void) player_id;
    ClassicAI* me = (ClassicAI*) obj;
    return (me->myboard.game_status() != 0);
  }



  ClassicAI::~ClassicAI() {
    if (score_players != NULL)
      delete[] score_players;
  }
  
  ClassicAI::ClassicAI(int id, const char* name, int depth,
		       int line, int column, int length, int nb_players):
    core(ClassicAI_fun::heuristique,
	 ClassicAI_fun::moves_getter,
	 ClassicAI_fun::play,
	 ClassicAI_fun::revert_play,
	 ClassicAI_fun::next_player,
	 ClassicAI_fun::last_move),
    myboard(line, column, length), name(name), id(id), depth(depth),
    n(line), m(column), l(length), nb_players(nb_players), score_players(NULL) 
  {
    score_players = new int[nb_players];
    for(int i = 0; i < nb_players; i++)
      score_players[i] = 0;
  }

  
  int ClassicAI::chooseMove(int player_id, int nb_moves, int *moves) {
    (void) nb_moves;
    (void) moves;
    int max_depth = depth;
    int remaining_moves = (myboard.get_max_length() * myboard.get_max_column()) - myboard.get_nb_pieces();
    if (depth > remaining_moves)
      max_depth = remaining_moves;
    int score1 = core.alpha_beta_time(max_depth, player_id, this, AI_TIME, false);
    int choice1 = core._best_move;
    printf("AB : Calculated (%d, %d):\n", countPlay, countReversePlay);
    //printf("Current score(j1 : %d, j2 : %d)\n", score_players[0], score_players[1]);
    countPlay = 0;
    countReversePlay = 0;
    /*
    int score2 = core.min_max(depth, player_id, this, false);
    int choice2 = core._best_move;
    printf("MM : Calculated (%d, %d):\n", countPlay, countReversePlay);
    if (choice1 != choice2 || score1 != score2)
      printf("AB : (%d, %d) MM : (%d, %d)\n", choice1, score1, choice2, score2);
    printf("Calculated (%d, %d):\n", countPlay, countReversePlay);*/
    printf("Choice : %d (score : %d)\n", choice1, score1);
    return choice1;
  }

  void ClassicAI::status() {
    printf("Player n°%d: ClassicAI %s\n", id, name);
  }

  void ClassicAI::play(int player_id, int move_id) {
    if (myboard.play(player_id, move_id) == -1) {
      printf("Unexpected move !\n");
      myboard.display_board();
      printf("Trying to play in %d\n", move_id);
      throw "error system";
    }
    int moveId = myboard.get_last_pos();
    calculateScore(moveId, player_id);
    
    countPlay = 0;
    countReversePlay = 0;
 
    //myboard.display_board();
    //printf("==============\n");
  };

  /*
  int myPow(int value, int exponent) {
    
  }*/
  int attrib_score(int x) {
    int score = 1;
    while(--x > 0)
      score *= 5;
    return score;
  }
  int basicScore(Connect4& myboard, int id) {
    int h = myboard.nb_horizontal(id);
    int v = myboard.nb_vertical(id);
    int dr = myboard.nb_diag_dr(id);
    int ur = myboard.nb_diag_ur(id);
    return attrib_score(h)
      + attrib_score(v)
      + attrib_score(dr)
      + attrib_score(ur);
  }

  int myScore(Connect4& myboard, int id) {
    int l = myboard.get_max_length();
    /*
    int n = myboard.get_max_line();
    int m = myboard.get_max_column();
    int l = myboard.get_max_length();
    int line = myboard.get_line(id);
    int column = myboard.get_column(id);*/
    
    int hM = myboard.nb_horizontal(id, true);
    int vM = myboard.nb_vertical(id, true);
    int drM = myboard.nb_diag_dr(id, true);
    int urM = myboard.nb_diag_ur(id, true);

    int h = myboard.nb_horizontal(id);
    int v = myboard.nb_vertical(id);
    int dr = myboard.nb_diag_dr(id);
    int ur = myboard.nb_diag_ur(id);
    if (vM < l) v = 0;
    if (hM < l) h = 0;
    if (drM < l) dr = 0;
    if (urM < l) ur = 0;
    int total = v*vM + h*hM*hM*2 + dr*drM*drM*4 + ur*urM*urM*4;
    return total;
  }

  int getScore(Connect4& myboard, int id) {
    return basicScore(myboard, id);
  }
  
  void ClassicAI::calculateScore(int id, int player_id) {
    score_players[player_id -1] += getScore(myboard, id);
  }

  void ClassicAI::remove_piece(int column, int player_id) {
    int piece_id = myboard.get_id_col(column);
    score_players[player_id -1] -= getScore(myboard, piece_id);
    myboard.remove_piece(column);
  }
}
