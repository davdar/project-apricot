#include "GameApp.h"

#include <SDL.h>
#include <SDL_image.h>

#include "Grid.h"
#include "rendering/Animation.h"
#include "rendering/Sprite.h"
#include "rendering/SDLRenderer.h"
#include "rendering/Scene.h"

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

	

	gameGrid = new ConstantGrid(640, 480, 0);
	renderer = new SDLRenderer();
	renderer->init();

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

	scene = new Scene(Vector2(1600, 1600));
	scene->getLayers()[Layer::MAIN].push_back(frogSprite);
}

void GameApp::shutdown(){
	delete gameGrid;

	SDL_Quit();
}

void GameApp::handleEvents(){
	SDL_Event event;
	Vector2 pos;

	while(SDL_PollEvent( &event )){
		switch(event.type){
		case SDL_QUIT:
			this->quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			pos = Vector2(event.button.x, event.button.y);
			pos += renderer->getViewportPos();
			frogSprite->setTranslation(pos);
			break;
		case SDL_KEYDOWN:
			pos = renderer->getViewportPos();
			switch(event.key.keysym.sym){
			case SDLKey::SDLK_DOWN:
				pos += Vector2(0, 10);
				break;
			case SDLKey::SDLK_UP:
				pos -= Vector2(0, 10);
				break;
			case SDLKey::SDLK_LEFT:
				pos -= Vector2(10, 0);
				break;
			case SDLKey::SDLK_RIGHT:
				pos += Vector2(10, 0);
				break;
			}
			renderer->setViewportPos(pos);
			break;
		}
	}
}

void GameApp::runGame(){

}

void GameApp::render(){
	renderer->clear();
	renderer->renderScene(scene);
	renderer->flip();
}