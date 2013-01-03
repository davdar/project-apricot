#ifndef _GAME_APP_H
#define _GAME_APP_H

class GameApp {
	
public:
	void run();

protected:
	virtual void handleEvents(){}
	virtual void runGame(){}
	virtual void render(){}
};


#endif
