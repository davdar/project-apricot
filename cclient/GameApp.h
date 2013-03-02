#ifndef _GAME_APP_H
#define _GAME_APP_H

#include "types.h"

class Grid;
class Animation;
class SDL_Surface;
class Sprite;
class Renderer;
class Scene;

/*
 * The main app that drives the game.
 */
class GameApp {
public:
	enum Layer {
		MAIN = 100
	};
	
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
	Sprite *frogSprite;
	Renderer *renderer;


private:
	bool quit; //When this is true, we should quit the game
};

#endif