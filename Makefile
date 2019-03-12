CPPFLAGS=-Wall -Werror

GA=games
PL=players
BLD=build
NECESSARY=rectangular_board.o main.o human.o random_player.o alpha_beta.o alpha_beta_time.o classic_ai.o connect4.o

game: ${NECESSARY}
	g++ ${CPPFLAGS} $^ -o $@

main.o : main.cpp ${PL}/random_player.hpp ${GA}/connect4.hpp ${PL}/player.hpp ${PL}/human.hpp
	g++ ${CPPFLAGS} -c $<

rectangular_board.o: ${GA}/rectangular_board.cpp ${GA}/rectangular_board.hpp
	g++ ${CPPFLAGS} -c $<

rectangular_board_fun.o: ${GA}/rectangular_board_fun.cpp ${GA}/rectangular_board_fun.hpp
	g++ ${CPPFLAGS} -c $<

connect4.o: ${GA}/connect4.cpp ${GA}/game.hpp ${GA}/connect4.hpp
	g++ ${CPPFLAGS} -c $<

human.o: ${PL}/human.cpp ${PL}/player.hpp ${PL}/human.hpp
	g++ ${CPPFLAGS} -c $<

random_player.o: ${PL}/random_player.cpp ${PL}/player.hpp ${PL}/random_player.hpp
	g++ ${CPPFLAGS} -c $<

alpha_beta.o: ${PL}/alpha_beta.cpp ${PL}/alpha_beta.hpp 
	g++ ${CPPFLAGS} -c $<

alpha_beta_time.o: ${PL}/alpha_beta_time.cpp ${PL}/alpha_beta_time.hpp 
	g++ ${CPPFLAGS} -c $<

classic_ai.o: ${PL}/classic_ai.cpp ${GA}/connect4.hpp ${PL}/classic_ai.hpp ${PL}/alpha_beta.hpp
	g++ ${CPPFLAGS} -c $<

clean:
	rm -rf *.o game *~


#%o: %.cpp
#	g++ ${CPPFLAGS} -c $<
