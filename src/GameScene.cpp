#include "GameScene.hh"

#include "Game.h"
#include "Camera.h"
#include "Input.h"
#include "Graphics.h"
#include "Pathfinding.hh"
#include <unistd.h>
#include "LoseScene.hh"


int abs(int i) {
	if (i < 0) return i * -1;
	else return i;
}

int distance(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}


void GameScene::update() {
	
	//Pathfinding::findPath(*map, 1, 1, 0, 0);
	
	if (rip > 0) {
		LoseScene *loseScene = new LoseScene(game, menuScene, score); // this will leak memory D:
		game->setScene(loseScene);
	}
	/*if (rip > 0) {
		if (rip >= 10) game->setScene(menuScene);
		else rip++;
	}*/
	
	if (alienTurn) {
		bool allAliensDone = true;
		for (int i = 0; i < Aliens.size(); i++) {
			if ( Aliens[i].update(&player, *map) ); // if one alien is done update next
			else { // if some alien is not done do not end turn
				allAliensDone = false;
				break;
			}
		}
		
		// end of turn
		if (allAliensDone) {
			for (int i = 0; i < Aliens.size(); i++) {
				Aliens[i].done = false;
				Aliens[i].resetAP();
			}
			alienTurn = false;
			turn++;
			score++;
		}
	}
	else if (grenadeTurn) {
		if (grenadeX != aimX || grenadeY != aimY) {
		
			if (!lastWasX && grenadeX != aimX) { // nedd X and dont skip
				if (grenadeX > aimX) {
					grenadeX--;
				}
				else {
					grenadeX++;
				}
				lastWasX = true;
			}
			else if (grenadeY != aimY) { // need Y
				if (grenadeY > aimY) {
					grenadeY--;
				}
				else {
					grenadeY++;
				}
				lastWasX = false;
			}
			else { // need X, skip but Y not needed
				if (grenadeX > aimX) {
					grenadeX--;
				}
				else {
					grenadeX++;
				}
				lastWasX = true;
			}
		
		}
		else {
			if (boom >= 4) {
				grenadeTurn = false;
				// Do damage
				if (distance(player.getX(), player.getY(), grenadeX, grenadeY) < 4) {
					player.changeHealth(-10);
				}
				// aliens
				for (int i = 0; i < Aliens.size(); i++) {
					if (distance(Aliens[i].getX(), Aliens[i].getY(), grenadeX, grenadeY) < 4) {
						Aliens[i].changeHealth(-10);
					}
				}
			}
			else {
				boom++;
			}
		}
	}
	else {
		// input
		if (game->input.isButtonDown(tplay::Keyboard::Q) || game->input.isButtonDown(tplay::Keyboard::ESCAPE)) {
			game->setScene(menuScene);
		}
		else if (game->input.isButtonDown(tplay::Keyboard::W)) {
			if (aiming) {
				if(distance(player.getX(), player.getY(), aimX, aimY + 1) <= aimDist) aimY++;
			}
			else if (player.getAP() > 0 && !map->collidesAt(player.getX(), player.getY() + 1)) {
				player.move(0, 1);
				player.changeAP(-1);
			}
		}
		else if (game->input.isButtonDown(tplay::Keyboard::S)) {
			if (aiming) {
				if(distance(player.getX(), player.getY(), aimX, aimY - 1) <= aimDist) aimY--;
			}
			else if (player.getAP() > 0 && !map->collidesAt(player.getX(), player.getY() - 1)) {
				player.move(0, -1);
				player.changeAP(-1);
			}
		}
		else if (game->input.isButtonDown(tplay::Keyboard::A)) {
			if (aiming) {
				if(distance(player.getX(), player.getY(), aimX - 1, aimY) <= aimDist) aimX--;
			}
			else if (player.getAP() > 0 && !map->collidesAt(player.getX() - 1, player.getY())) {
				player.move(-1, 0);
				player.changeAP(-1);
			}
		}
		else if (game->input.isButtonDown(tplay::Keyboard::D)) {
			if (aiming) {
				if(distance(player.getX(), player.getY(), aimX + 1, aimY) <= aimDist) aimX++;
			}
			else if (player.getAP() > 0 && !map->collidesAt(player.getX() + 1, player.getY())) {
				player.move(1, 0);
				player.changeAP(-1);
			}
		}
		else if (game->input.isButtonDown(tplay::Keyboard::ENTER)) {
			if (aiming && player.getAP() >= 5 && player.getGrenades() > 0) {
				player.changeAP(-5);
				player.changeGrenades(-1);
				grenadeX = player.getX();
				grenadeY = player.getY();
				grenadeTurn = true;
				aiming = false;
				boom = -5;
			}
			else if (!aiming) {
				alienTurn = true;
				player.resetAP();
				
				if (turn % 10 == 0) {
					// do spawn
					Aliens.push_back(*new Alien(-15, 9));
					Aliens.push_back(*new Alien(-50, -8));
					Aliens.push_back(*new Alien(49, -1));
					
					player.changeGrenades(1);
					player.changeHealth(1);
				}
				
			}
		}
		else if (game->input.isButtonDown(tplay::Keyboard::SPACEBAR)) {
			aiming = !aiming;
			if (aiming) {
				aimX = player.getX();
				aimY = player.getY();
			}
		}
	}
	
	// general checks
	
	if (player.getHealth() <= 0) {
		rip = true;
	}
	
}


void GameScene::draw() {
	game->graphics.setCamera(&camera);
	camera.setCoordinates(player.getX() - game->graphics.getTerminalSizeX() / 2, player.getY() - game->graphics.getTerminalSizeY() / 2);
	
	// Level
	map->draw();
	
	// Alions
	for (int i = 0; i  < Aliens.size(); i++) {
		if(Aliens[i].getHealth() <= 0) {
			game->graphics.addToWorld(Aliens[i].getX(), Aliens[i].getY(), "_");
		}
		else if (Aliens[i].isShit()) {
			game->graphics.addToWorld(Aliens[i].getX(), Aliens[i].getY(), "a");
		}
		else {
			game->graphics.addToWorld(Aliens[i].getX(), Aliens[i].getY(), "A");
		}
	}
	
	// Player
	game->graphics.addToWorld(player.getX(), player.getY(), "@");
	
	// Aiming
	if (aiming) {
		game->graphics.addToWorld(aimX, aimY, "X");
	}
	
	// Throwing
	if (grenadeTurn) {
		if (boom > 0) {
			if (boom == 1) {
				game->graphics.addToWorld(grenadeX, grenadeY, "*");
			}
			if (boom == 2) {
				game->graphics.addToWorld(grenadeX, grenadeY + 1, "*");
				game->graphics.addToWorld(grenadeX - 1, grenadeY, "***");
				game->graphics.addToWorld(grenadeX, grenadeY - 1, "*");
			}
			if (boom == 3) {
				game->graphics.addToWorld(grenadeX, grenadeY + 2, "*");
				game->graphics.addToWorld(grenadeX - 1, grenadeY + 1, "***");
				game->graphics.addToWorld(grenadeX - 2, grenadeY, "*****");
				game->graphics.addToWorld(grenadeX - 1, grenadeY - 1, "***");
				game->graphics.addToWorld(grenadeX, grenadeY - 2, "*");
			}
			if (boom == 4) {
				game->graphics.addToWorld(grenadeX, grenadeY + 3, "*");
				game->graphics.addToWorld(grenadeX - 1, grenadeY + 2, "***");
				game->graphics.addToWorld(grenadeX - 2, grenadeY + 1, "*****");
				game->graphics.addToWorld(grenadeX - 3, grenadeY, "*******");
				game->graphics.addToWorld(grenadeX - 2, grenadeY - 1, "*****");
				game->graphics.addToWorld(grenadeX - 1, grenadeY - 2, "***");
				game->graphics.addToWorld(grenadeX, grenadeY - 3, "*");
			}
			usleep(400000);
		}
		else {
			game->graphics.addToWorld(grenadeX, grenadeY, "o");
		}
		usleep(100000);
	}
	
	// UI
	game->graphics.setFormat(tplay::Format::NEGATIVE);
	
	//top (game state)
	if (aiming) game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 3, game->graphics.getTerminalSizeY() - 1, "Aiming");
	if (grenadeTurn) game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 8, game->graphics.getTerminalSizeY() - 1, "Throwing grenade");
	if (alienTurn) game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 5, game->graphics.getTerminalSizeY() - 1, "Alien turn");
	//bottom
	for (int i = 0; i < game->graphics.getTerminalSizeX(); i++) {
		game->graphics.addToScreen(i, 0, " ");
	}
	game->graphics.addToScreen(0, 0, "Health: " + std::to_string(player.getHealth()));
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 3 - 6, 0, "Grenades: " + std::to_string(player.getGrenades()));
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 4, 0, "Turn: " + std::to_string(turn));
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 3 * 2 - 5, 0, "Score: " + std::to_string(score));
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() - 6, 0, "AP: " + std::to_string(player.getAP()));
	
	if (rip > 0) {
		game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 5, game->graphics.getTerminalSizeY() / 2 - 1, "           ");
		game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 5, game->graphics.getTerminalSizeY() / 2, " You died! ");
		game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 5, game->graphics.getTerminalSizeY() / 2 + 1, "           ");
		usleep(1000000);
	}
	
	//game->graphics.addToScreen(0, game->graphics.getTerminalSizeY() / 2, " Num of aliens: " + std::to_string(Aliens.size()));
	
	game->graphics.unsetFormat(tplay::Format::NEGATIVE);
	
}
