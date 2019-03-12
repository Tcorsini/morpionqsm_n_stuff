#include "games/connect4.hpp"
#include "players/human.hpp"
#include "players/random_player.hpp"
#include "players/classic_ai.hpp"
#include <cstdio>
#include <stdlib.h>

#define NB_PLAYERS 2
#define DIFF 100
#define MAX_TRIES 5

int next_player(int player_id) {
  return 1 + player_id % NB_PLAYERS;
}

static const char* names[] = {"toto", "titi", "chips", "patate"};

int connect4_loop(int argc, char** argv) {
  int n = 6;
  int m = 7;
  int l = 4;
  if (argc >= 4) {
    n = atoi(argv[1]);
    m = atoi(argv[2]);
    l = atoi(argv[3]);
  }
  timGames::Connect4 b(n, m, l);
  Player* P[NB_PLAYERS];
  //P[0] = new timGames::ClassicAI(1, names[0], 9, n, m, l, NB_PLAYERS);
  P[0] = new Human(1, names[1]);//, DIFF, n, m, l, NB_PLAYERS);
  //P[1] = new Human(2, names[1]);
  //P[0] = new RandomPlayer(1 + 0, names[0]);
  P[1] = new timGames::ClassicAI(2, names[0], DIFF, n, m, l, NB_PLAYERS);
  //P[1] = new morpion::ClassicAI(2, names[1], DIFF, n, m, l, NB_PLAYERS);
  /*
  for(int i = 1; i < NB_PLAYERS; i++) {
    P[i] = new RandomPlayer(1 + i, names[i]);
    P[i]->status();
    }*/
  int id = 1;
  int* moves;
  int status = 0;
  while((status = b.game_status()) == 0) {
    b.display_board();
    Player* p = P[id-1];
    p->status();
    int nb_moves = b.get_moves(id, &moves);
    int action = p->chooseMove(id, nb_moves, moves);
    int tries = 0;
    while(b.play(id, action) < 0 && tries++ < MAX_TRIES) {
      printf("Invalid action(%d), try again :\n", action);
      action = p->chooseMove(id, nb_moves, moves);
    }
    if (tries >= MAX_TRIES) {
      printf("Aborted the game");
      return 1;
    }
    printf("Le joueur %d joue en %d", id, action);
    int jeton = b.get_id_col(action);
    printf("(id : %d, h : %d/%d, v : %d/%d, dr : %d/%d, ur : %d/%d)", jeton,
	   b.nb_horizontal(jeton), b.nb_horizontal(jeton, true),
	   b.nb_vertical(jeton), b.nb_vertical(jeton, true),
	   b.nb_diag_dr(jeton), b.nb_diag_dr(jeton, true),
	   b.nb_diag_ur(jeton), b.nb_diag_ur(jeton, true));
	   printf(" !\n");
    printf("%d pieces jouées !\n", b.get_nb_pieces());
    //b.revert_play();
    for(int i = 0; i < NB_PLAYERS; i++)
      P[i]->play(id, action); //met à jour la vue de tous les joueurs
    
    delete[] moves;
    id = next_player(id);
  }
  b.display_board();
  if (status == -1)
    printf("Pas de gagnant !\n");
  else {
    printf("Le gagnant est...");
    P[status-1]->status();
  }
  for(int i = 0; i < NB_PLAYERS; i++) {
    delete P[i];
  }
  return 0;
}


int main(int argc, char**argv) {
  return connect4_loop(argc, argv);
}
