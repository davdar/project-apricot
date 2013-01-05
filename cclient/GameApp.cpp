#include "GameApp.h"

#include <SDL.h>

void GameApp::run(){
	//Run the game loop
	while(!this->quit){
		handleEvents();
		runGame();
		render();
	}
}


void GameApp::handleEvents(){
	SDL_Event event;

	while(SDL_PollEvent( &event )){
		switch(event.type){
		case SDL_QUIT:
			this->quit = true;
		}
	}
}

void GameApp::runGame(){

}

void GameApp::render(){

}