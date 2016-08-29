#include "Alien.hh"
#include "Player.hh"
#include "Map.hh"
#include "Pathfinding.hh"


Alien::Alien(int x, int y) {
	this->x = x;
	this->y = y;
}


int aBs(int i) {
	if (i < 0) return i * -1;
	else return i;
}

int distanc(int x1, int y1, int x2, int y2) {
	return aBs(x1 - x2) + aBs(y1 - y2);
}


bool Alien::update(Player *player, Map map) {
	if (AP > 0 && !done && health > 0) {
		if (distanc(x, y, player->getX(), player->getY()) <= 1) {
			player->changeHealth(-1);
			done = true;
			return true;
		}
		else if (!isShit() && AP > 0) { // see if alien can shoot TODO
			if (distanc(x, y, player->getX(), player->getY()) <= 1) {
				return true; // ////////////////////////////// shoot shit TODO TODO TODO PLZ
			}
			else {
				if (x != player->getX() || y != player->getY()) {
				
					if (!lastWasX && x != player->getX()) { // nedd X and dont skip
						if (x > player->getX()) {
							x--;
						}
						else {
							x++;
						}
						lastWasX = true;
					}
					else if (y != player->getY()) { // need Y
						if (y > player->getY()) {
							y--;
						}
						else {
							y++;
						}
						lastWasX = false;
					}
					else { // need X, skip but Y not needed
						if (x > player->getX()) {
							x--;
						}
						else {
							x++;
						}
						lastWasX = true;
					}
				
				}
			}
			
			AP--;
			return false;
		}
		else if (AP > 0) { // just go
			//Pathfinding::findPath(map, x, y, player->getX(), player->getY()); // riped dreams are made of this
			
			
			if (x != player->getX() || y != player->getY()) {
			
				if (!lastWasX && x != player->getX()) { // nedd X and dont skip
					if (x > player->getX()) {
						x--;
					}
					else {
						x++;
					}
					lastWasX = true;
				}
				else if (y != player->getY()) { // need Y
					if (y > player->getY()) {
						y--;
					}
					else {
						y++;
					}
					lastWasX = false;
				}
				else { // need X, skip but Y not needed
					if (x > player->getX()) {
						x--;
					}
					else {
						x++;
					}
					lastWasX = true;
				}
			
			}
			
			AP--;
			return false; // WIP
		}
	}
	else return true;
}


int Alien::getX() {
	return x;
}


int Alien::getY() {
	return y;
}


void Alien::move(int x, int y) {
	this->x += x;
	this->y += y;
}


int Alien::getHealth() {
	return health;
}


void Alien::changeHealth(int change) {
	this->health += change;
	if (health <= 10) {
		shit = true; // alien becomes shitty
		baseAP = 5;
	}
}


int Alien::getAP() {
	return AP;
}


void Alien::resetAP() {
	AP = baseAP;
}


bool Alien::isShit() {
	return shit;
}