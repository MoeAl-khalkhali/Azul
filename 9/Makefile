.default: all

all: assign2

clean:
		rm -rf assign2 *.o *.dSYM

assign2: Tile.o TileFactory.o TileBag.o main.o Player.o Binlid.o Mosaic.o
		g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
		g++ -Wall -Werror -std=c++14 -g -O -c $^

