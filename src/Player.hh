#ifndef PLAYER_H
#define PLAYER_H

class Player {
	private:
		int x = 0, y = 0;
		int maxHealth = 10;
		int health = 10;
		int grenades = 10;
		int baseAP = 15;
		int AP = baseAP;
	
	public:
		
		int getX();
		int getY();
		void move(int x, int y);
		int getHealth();
		void changeHealth(int change);
		int getGrenades();
		void changeGrenades(int grenades);
		int getAP();
		void changeAP(int AP);
		void resetAP();
	
};

#endif
