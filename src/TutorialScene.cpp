#include "TutorialScene.hh"

#include "Game.h"
#include "Camera.h"
#include "Input.h"


void TutorialScene::update() {
	// input
	if (game->input.isButtonDown(tplay::Keyboard::ENTER)) {
		game->setScene(menuScene);
	}
	else if (game->input.isButtonDown(tplay::Keyboard::UP_ARROW) || game->input.isButtonDown(tplay::Keyboard::W)) {
		
	}
	else if (game->input.isButtonDown(tplay::Keyboard::DOWN_ARROW) || game->input.isButtonDown(tplay::Keyboard::S)) {
		
	}
	else if (game->input.isButtonDown(tplay::Keyboard::ENTER)) {
		
	}
	
}


void TutorialScene::draw() {
	game->graphics.setCamera(&camera);
	
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 10, game->graphics.getTerminalSizeY() / 2 + 2, "TODO: write tutorial");
	game->graphics.setFormat(tplay::Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 6, game->graphics.getTerminalSizeY() / 2 - 4, "back to menu");
	game->graphics.unsetFormat(tplay::Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 10, game->graphics.getTerminalSizeY() / 2 - 2 * 2, ">");
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 + 10, game->graphics.getTerminalSizeY() / 2 - 2 * 2, "<");
}
