#ifndef _GAME_APP_H
#define _GAME_APP_H

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

protected:
	bool quit; //When this is true, we should quit the game
};

#endif