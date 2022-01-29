COMPILER = g++ -O2 -Wall -g
SRC = src/
FILES = $(SRC)main.cpp $(SRC)maze.cpp $(SRC)matrix.cpp $(SRC)path.cpp $(SRC)game.cpp

aimaze: $(FILES)
	$(COMPILER) $(FILES) -o aimaze -lncurses

clean: 
	rm -rf aimaze