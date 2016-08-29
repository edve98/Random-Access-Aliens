#include "Player.hh"


int Player::getX() {
	return x;
}


int Player::getY() {
	return y;
}


void Player::move(int x, int y) {
	this->x += x;
	this->y += y;
}


int Player::getHealth() {
	return health;
}


void Player::changeHealth(int change) {
	if (health + change > maxHealth) this->health = maxHealth; 
	else this->health += change;
}


int Player::getGrenades() {
	return grenades;
}


void Player::changeGrenades(int grenades) {
	this->grenades += grenades;
}


int Player::getAP() {
	return AP;
}


void Player::changeAP(int AP) {
	this->AP += AP;
}


void Player::resetAP() {
	AP = baseAP;
}