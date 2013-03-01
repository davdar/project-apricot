#include "GameApp.h"

#include <SDL.h>
#include <SDL_image.h>

#include "Grid.h"
#include "rendering/Animation.h"
#include "rendering/Sprite.h"
#include "rendering/SDLRenderer.h"

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

	screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(screen == NULL){
		fprintf(stderr, "Unable to create video window!");
	}

	gameGrid = new ConstantGrid(640, 480, 0);
	renderer = new SDLRenderer(screen);

	SDL_Surface *frogImg = IMG_Load("froggy_32x32.png");
	if ( !frogImg )
	{
		printf ( "IMG_Load: %s\n", IMG_GetError () );
		exit(1);
	}
	SDL_Surface **frogAnim = new SDL_Surface*[1];
	frogAnim[0] = frogImg;

	frog = new Animation(frogImg->w, frogImg->h, 1, frogAnim);
	frogSprite = new Sprite();
	frogSprite->setAnimation(frog);
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
		case SDL_MOUSEBUTTONDOWN:
			frogSprite->setTranslation(Vector2(event.button.x, event.button.y));
		}
	}
}

void GameApp::runGame(){

}

void GameApp::render(){
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	renderer->drawSprite(frogSprite);

	SDL_Flip(screen);
	
}