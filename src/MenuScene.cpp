#include "MenuScene.hh"

#include "Game.h"
#include "Camera.h"
#include "Input.h"
#include "Scene.h"
#include "GameScene.hh"


void MenuScene::setScenes(tplay::Scene *one, tplay::Scene *two) {
	this->tutorialScene = one;
	this->gameScene = two;
}


void MenuScene::onEnter() {
	selectedID = 0;
}


void MenuScene::update() {
	// input
	if (game->input.isButtonDown(tplay::Keyboard::Q) || game->input.isButtonDown(tplay::Keyboard::ESCAPE)) {
		game->quit();
	}
	else if (game->input.isButtonDown(tplay::Keyboard::UP_ARROW) || game->input.isButtonDown(tplay::Keyboard::W)) {
		if (!selectedID <= 0) {
			selectedID--;
		}
	}
	else if (game->input.isButtonDown(tplay::Keyboard::DOWN_ARROW) || game->input.isButtonDown(tplay::Keyboard::S)) {
		if (selectedID <= 1) {
			selectedID++;
		}
	}
	else if (game->input.isButtonDown(tplay::Keyboard::ENTER)) {
		useMenu();
	}
	
}


void MenuScene::draw() {
	game->graphics.setCamera(&camera);
	
	// Name
	game->graphics.setFormat(tplay::Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 11, game->graphics.getTerminalSizeY() / 2 + 5 - 1, "                      ");
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 11, game->graphics.getTerminalSizeY() / 2 + 5, " Random Access Aliens ");
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 11, game->graphics.getTerminalSizeY() / 2 + 5 + 1, "                      ");
	game->graphics.unsetFormat(tplay::Format::NEGATIVE);
	
	// Menu items
	if (selectedID == 0) game->graphics.setFormat(tplay::Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 2, game->graphics.getTerminalSizeY() / 2, "Play");
	if (selectedID == 0) game->graphics.unsetFormat(tplay::Format::NEGATIVE);
	
	if (selectedID == 1) game->graphics.setFormat(tplay::Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 4, game->graphics.getTerminalSizeY() / 2 - 2, "Tutorial");
	if (selectedID == 1) game->graphics.unsetFormat(tplay::Format::NEGATIVE);
	
	if (selectedID == 2) game->graphics.setFormat(tplay::Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 2, game->graphics.getTerminalSizeY() / 2 - 4, "Quit");
	if (selectedID == 2) game->graphics.unsetFormat(tplay::Format::NEGATIVE);
	
	// Arrows for menu
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 10, game->graphics.getTerminalSizeY() / 2 - selectedID * 2, ">");
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 + 10, game->graphics.getTerminalSizeY() / 2 - selectedID * 2, "<");
	
}


void MenuScene::useMenu() {
	
	switch (selectedID) {
		case 0:
			gameScene = new GameScene(game, this);
			game->setScene(gameScene);
			break;
		
		case 1:
			game->setScene(tutorialScene);
			break;
		
		case 2:
			game->quit();
			break;
		
	}
}
