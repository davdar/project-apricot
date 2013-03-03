#ifndef _GAME_APP_H
#define _GAME_APP_H

#include "types.h"

class Grid;
class Animation;
class SDL_Surface;
class AnimationSprite;
class Renderer;
class Scene;
class SceneObject;
class WorldMap;


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
	AnimationSprite *frogSprite;
	SceneObject *frogSceneObject;
	Renderer *renderer;
	WorldMap *worldMap;

	SDL_Surface *screen;


private:
	bool quit; //When this is true, we should quit the game
};

#endif