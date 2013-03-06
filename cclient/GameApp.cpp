#include "GameApp.h"

#include <SDL.h>
#include <SDL_image.h>

#include "Grid.h"
#include "WorldMap.h"
#include "rendering/Animation.h"
#include "rendering/AnimationSprite.h"
#include "rendering/Renderer.h"
#include "rendering/SDLRenderer.h"
#include "rendering/Scene.h"

const int GameApp::MAIN_LAYER = 100;

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

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

	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	gameGrid = new CheckerGrid(50, 50, 0, 255);
	worldMap = new WorldMap();
	worldMap->setMapGrid(gameGrid);
	
	renderer = new SDLRenderer();
	renderer->init(SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Surface *frogImg = IMG_Load("froggy_32x32.png");
	if ( !frogImg )
	{
		printf ( "IMG_Load: %s\n", IMG_GetError () );
		exit(1);
	}
	SDL_Surface **frogAnim = new SDL_Surface*[1];
	frogAnim[0] = frogImg;

	frog = new Animation(frogImg->w, frogImg->h, 1, frogAnim);
	frogSprite = new AnimationSprite(Vector2(0,0), Vector2(0,0), 0, frog);

	scene = new Scene(Vector2(1600, 1600));
	scene->getLayers()[MAIN_LAYER].push_back(frogSprite);
	scene->getLayers()[MAIN_LAYER-1].push_back(worldMap);
}

void GameApp::shutdown(){
	delete gameGrid;

	renderer->uninit();
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
			frogSprite->setPosition(pos);
			break;
		case SDL_KEYDOWN:
			pos = renderer->getViewportPos();
			switch(event.key.keysym.sym){
			case SDLK_DOWN:
				pos += Vector2(0, 10);
				break;
			case SDLK_UP:
				pos -= Vector2(0, 10);
				break;
			case SDLK_LEFT:
				pos -= Vector2(10, 0);
				break;
			case SDLK_RIGHT:
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
	renderer->setTransform(Identity3x3);
	renderer->fillRect(Vector4(0,0,SCREEN_WIDTH,SCREEN_HEIGHT),
						Vector4(0, 0, 0, 1.0));
	renderer->setTransform(renderer->getDefaultTransform());
	renderer->drawScene(scene);
	renderer->swapBuffer();
}
