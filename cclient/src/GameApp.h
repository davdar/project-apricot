#ifndef _GAME_APP_H
#define _GAME_APP_H

#include "types.h"
#include "vector.h"

class Grid;
class Animation;
class AnimationSprite;
class Renderer;
class Scene;
class WorldMap;
class WorldMapSprite;


/*
 * The main app that drives the game.
 */
class GameApp {
public:
	static const int MAIN_LAYER;	

public:
	GameApp();
	void run();

protected:
	void handleEvents();
	void runGame();
	void render();

	void startup();
	void shutdown();

protected:
	Grid *gameGrid;
	Vector2 viewportPos;

	//For testing
	shared_ptr<Animation> frog;
	Scene *scene;
	AnimationSprite *frogSprite;
	Renderer *renderer;
	shared_ptr<WorldMap> worldMap;
	WorldMapSprite *worldMapSprite;


private:
	bool quit; //When this is true, we should quit the game
};

#endif
