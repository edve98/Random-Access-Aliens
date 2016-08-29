#ifndef GAMESCENE_H
#define GAMESCENE_H


#include "Game.h"
#include "Camera.h"
#include "Player.hh"
#include "Alien.hh"
#include "Map.hh"
#include <vector>


class GameScene : public tplay::Scene {
	public:
		tplay::Game *game;
		tplay::Camera camera;
		tplay::Scene *menuScene;
		Player player;
		Map *map;
		bool aiming = false;
		bool alienTurn = false;
		bool grenadeTurn = false;
		int aimX, aimY;
		int aimDist = 10;
		int turn = 0;
		int score = 0;
		std::vector<Alien> Aliens;
		int rip = 0;
		
		// grenade vars
		int grenadeX, grenadeY;
		int boom = -5; // explosion state (yeah I know)
		
		bool lastWasX = false; // general animation coolness
		
		GameScene(tplay::Game *game, tplay::Scene *menuScene) {
			this->game = game;
			this->menuScene = menuScene;
			map = new Map(game);
		}
		
		void update();
		void draw();
};

#endif
