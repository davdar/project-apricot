#ifndef _GAME_APP_H
#define _GAME_APP_H

#include "types.h"

class Grid;
class Animation;
class AnimationSprite;
class Renderer;
class Scene;
class WorldMap;


/*
 * The main app that drives the game.
 */
class GameApp {
public:
	static const int MAIN_LAYER;	
public:
	void run();

protected:
	void handleEvents();
	void runGame();
	void render();

	void startup();
	void shutdown();

protected:
	Grid *gameGrid;

	//For testing
	Animation *frog;
	Scene *scene;
	AnimationSprite *frogSprite;
	Renderer *renderer;
	WorldMap *worldMap;


private:
	bool quit; //When this is true, we should quit the game
};

#endif
