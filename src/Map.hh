#ifndef MAP_H
#define MAP_H


#include <cstdio>
#include "Game.h"
#include "Graphics.h"
#include <string>

class Map {
	private:
		FILE * filep = fopen("map.txt", "r");
		tplay::Game *game;
	
	public:
		int sizeX = 0, sizeY = 0;
		std::string map[200][200];
		Map(tplay::Game *game);
		bool collidesAt(int x, int y);
		void draw();
	
};


#endif
