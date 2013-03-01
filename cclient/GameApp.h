#ifndef _GAME_APP_H
#define _GAME_APP_H

#include "types.h"

class Grid;
class Animation;
class SDL_Surface;
class Sprite;
class Renderer;

/*
 * The main app that drives the game.
 */
class GameApp {
	
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
	SDL_Surface *screen;
	Sprite *frogSprite;
	Renderer *renderer;


private:
	bool quit; //When this is true, we should quit the game
};

#endif