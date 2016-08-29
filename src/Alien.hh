#ifndef ALIEN_H
#define ALIEN_H


#include "Player.hh"
#include "Map.hh"


class Alien {
	private:
		int x = 10, y = 9;
		int maxHealth = 100;
		int health = 20;
		int baseAP = 10;
		int AP = baseAP;
		bool shit = false;
		bool lastWasX = false;
	
	public:
		bool done = false;
		
		Alien(int x, int y);
		bool update(Player *player, Map map); // return true if done
		int getX();
		int getY();
		void move(int x, int y);
		int getHealth();
		void changeHealth(int change);
		int getAP();
		void resetAP();
		bool isShit();
	
};

#endif
