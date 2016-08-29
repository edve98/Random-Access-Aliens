#ifndef MENUSCENE_H
#define MENUSCENE_H


#include "Game.h"
#include "Camera.h"
#include "Scene.h"
#include "GameScene.hh"


class MenuScene : public tplay::Scene {
	private:
		tplay::Game *game;
		tplay::Camera camera;
		
		int selectedID = 0;
		
		tplay::Scene *tutorialScene;
	
	public:
		tplay::Scene *gameScene;
		
		MenuScene(tplay::Game &game) : game(&game) {}
		void onEnter();
		void update();
		void draw();
		void setScenes(tplay::Scene *one, tplay::Scene *two);
		void useMenu();
		
};


#endif
