#include "Map.hh"

#include <cstdio>
#include "Game.h"
#include "Graphics.h"

Map::Map(tplay::Game *game) {
	this->game = game;
	
	char c = getc(filep);
	while (c != 'k') {
		if (c == '\n') {
			sizeY++;
			sizeX = 0;
		}
		else {
			map[sizeX][sizeY] = c;
			sizeX++;
		}
		if (c == '!') {
			printf("%i %i\n", sizeX, sizeY);
		}
		
		c = getc(filep);
	}
}


bool Map::collidesAt(int x, int y) {
	x = x + sizeX / 2;
	y = y + sizeY / 2;
	if (x > sizeX || x <  0 || y > sizeY || y < 0) return true;
	if (map[x][y] == " " ) return false;
	else return true;
}


void Map::draw() {
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y <= sizeY; y++) {
			game->graphics.addToWorld(x - sizeX / 2, y - sizeY / 2, map[x][y]);
		}
	}
}