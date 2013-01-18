#include "GameApp.h"

#include <SDL.h>
#include "Grid.h"


void GameApp::run(){
	startup();

	//Run the game loop
	while(!this->quit){
		handleEvents();
		runGame();
		render();
	}

	shutdown();
}

void GameApp::startup(){
	if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }

	SDL_Surface *screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(screen == NULL){
		fprintf(stderr, "Unable to create video window!");
	}

	gameGrid = new ConstantGrid(640, 480, 0);
}

void GameApp::shutdown(){
	delete gameGrid;

	SDL_Quit();
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