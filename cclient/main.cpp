/*
 * main.cpp - entry point for the program
 */

#include <stdio.h>
#include <SDL.h>
#include "GameApp.h"

int main(int argc, char* argv[]){
	if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }

	SDL_Surface *screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(screen == NULL){
		fprintf(stderr, "Unable to create video window!");
	}
  
	printf("Hello World!\n");

	GameApp *gameApp = new GameApp();

	gameApp->run();

    SDL_Quit();

	return 0;
}
