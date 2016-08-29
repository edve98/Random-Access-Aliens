#include "Game.h"
#include "Camera.h"
#include "Scene.h"


class TutorialScene : public tplay::Scene {
	public:
		tplay::Game *game;
		tplay::Camera camera;
		tplay::Scene *menuScene;
		
		TutorialScene(tplay::Game &game, tplay::Scene &menuScene) : game(&game), menuScene(&menuScene) {}
		
		void update();
		void draw();
};