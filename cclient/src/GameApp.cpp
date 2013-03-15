#include "GameApp.h"

#include <SDL.h>
#include <SDL_image.h>

#include "Grid.h"
#include "gamedata/WorldMap.h"
#include "rendering/SDLSurfaceAnimation.h"
#include "rendering/AnimationSprite.h"
#include "rendering/Renderer.h"
#include "rendering/SDLRenderer.h"
#include "rendering/Scene.h"
#include "sprite/WorldMapSprite.h"
#include "gamedata/GameData.h"

const int GameApp::MAIN_LAYER = 100;

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;
static const int MAP_CELL_PIXEL_WIDTH = 32;

GameApp::GameApp()
:quit(false)
,viewportPos(0,0){}

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
	worldMap = shared_ptr<WorldMap>(new WorldMap());
	worldMap->setMapGrid(gameGrid);

	worldMapSprite = new WorldMapSprite(MAP_CELL_PIXEL_WIDTH, worldMap);
	
	renderer = new SDLRenderer();
	renderer->init(SCREEN_WIDTH, SCREEN_HEIGHT);

	frog = renderer->loadAnimation("froggy_32x32.png");
	frogSprite = new AnimationSprite(Vector2(0,0), Vector2(0,0), 0, frog, NullGameData::getInstance());

	scene = new Scene(Vector2(1600, 1600));
	scene->getLayers()[MAIN_LAYER].push_back(frogSprite);
	scene->getLayers()[MAIN_LAYER-1].push_back(worldMapSprite);
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
			pos += viewportPos;
			frogSprite->setPosition(pos);
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			case SDLK_DOWN:
				viewportPos += Vector2(0, 10);
				break;
			case SDLK_UP:
				viewportPos -= Vector2(0, 10);
				break;
			case SDLK_LEFT:
				viewportPos -= Vector2(10, 0);
				break;
			case SDLK_RIGHT:
				viewportPos += Vector2(10, 0);
				break;
			}
			break;
		}
	}
}

void GameApp::runGame(){

}

void GameApp::render(){
	RenderContext screenContext = { Vector2(0,0) };
	RenderContext defaultContext = { viewportPos };

	renderer->fillRect(Vector4(0,0,SCREEN_WIDTH,SCREEN_HEIGHT),
						Vector4(0, 0, 0, 1.0), screenContext);

	renderer->drawScene(scene, defaultContext);
	renderer->swapBuffer();
}
