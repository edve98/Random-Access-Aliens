#include "LoseScene.hh"

#include "Game.h"
#include "Camera.h"
#include "Input.h"


#include <cstdio>


LoseScene::LoseScene(tplay::Game *game, tplay::Scene *menuScene, int score) {
	this->game = game;
	this->menuScene = menuScene;
	this->score = score;
	
	FILE *filep = fopen(".score", "r");
	fscanf(filep, "%i", &highscore);
	
	if (score > highscore) {
		filep = fopen(".score", "w");
		fprintf(filep, "%i\n", score);
		YESSS = true;
	}
	fclose(filep);
}


void LoseScene::update() {
	// input
	if (game->input.isButtonDown(tplay::Keyboard::ENTER)) {
		game->setScene(menuScene);
	}
	
}


void LoseScene::draw() {
	game->graphics.setCamera(&camera);
	
	// Name
	game->graphics.setFormat(tplay::Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 5, game->graphics.getTerminalSizeY() / 2 + 5, "Game over!");
	game->graphics.unsetFormat(tplay::Format::NEGATIVE);
	
	
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 9, game->graphics.getTerminalSizeY() / 2 + 3, "Your score was: " + std::to_string(score));
	if (YESSS) game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 11, game->graphics.getTerminalSizeY() / 2 + 2, "Last highscore was: " + std::to_string(highscore));
	else game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 12, game->graphics.getTerminalSizeY() / 2 + 2, "Current highscore is: " + std::to_string(highscore));
	
	if (YESSS) game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 22, game->graphics.getTerminalSizeY() / 2, "You just set the highscore, congratulations!");
	
	
	game->graphics.setFormat(tplay::Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 6, game->graphics.getTerminalSizeY() / 2 - 4, "back to menu");
	game->graphics.unsetFormat(tplay::Format::NEGATIVE);
	
	// Arrows for menu
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 10, game->graphics.getTerminalSizeY() / 2 - 2 * 2, ">");
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 + 10, game->graphics.getTerminalSizeY() / 2 - 2 * 2, "<");
	
}

