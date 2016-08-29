#include "Game.h"
#include "Camera.h"
#include "Scene.h"


class LoseScene : public tplay::Scene {
	private:
		tplay::Game *game;
		tplay::Camera camera;
		
		tplay::Scene *menuScene;
		
		int score, highscore;
		bool YESSS = false; // (true if new highscore is set)
	
	public:
		
		LoseScene(tplay::Game *game, tplay::Scene *menuScene, int score);
		void update();
		void draw();
		
};