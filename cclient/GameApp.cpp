#include "GameApp.h"

#include <SDL.h>
#include <SDL_image.h>

#include "Grid.h"
#include "WorldMap.h"
#include "rendering/Animation.h"
#include "rendering/AnimationSprite.h"
#include "rendering/Renderer.h"
#include "rendering/Scene.h"
#include "rendering/SceneObject.h"

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
	

	gameGrid = new CheckerGrid(50, 50, 0, 255);
	worldMap = new WorldMap();
	worldMap->setMapGrid(gameGrid);
	
	renderer = new Renderer(screen);

	SDL_Surface *frogImg = IMG_Load("froggy_32x32.png");
	if ( !frogImg )
	{
		printf ( "IMG_Load: %s\n", IMG_GetError () );
		exit(1);
	}
	SDL_Surface **frogAnim = new SDL_Surface*[1];
	frogAnim[0] = frogImg;

	frog = new Animation(frogImg->w, frogImg->h, 1, frogAnim);
	frogSprite = new AnimationSprite();
	frogSprite->setAnimation(frog);

	frogSceneObject = new SceneObject(frogSprite, Vector2(0,0), Vector2(32,32));

	scene = new Scene(Vector2(1600, 1600));
	scene->getLayers()[Layer::MAIN].push_back(frogSceneObject);
	scene->getLayers()[Layer::MAIN-1].push_back(new SceneObject(worldMap));
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
			frogSceneObject->setPosition(pos);
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
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	renderer->drawScene(scene);
	SDL_Flip(screen);
}