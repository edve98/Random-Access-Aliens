#include "Game.h"
#include "MenuScene.hh"
#include "GameScene.hh"
#include "TutorialScene.hh"


int main() {
	tplay::Game game;
	MenuScene menuScene(game);
	TutorialScene tutorialScene(game, menuScene);
	GameScene *gameScene = new GameScene(&game, &menuScene);
	menuScene.setScenes(&tutorialScene, gameScene);
	game.setScene(&menuScene);
	game.loop();
	return 0;
}
