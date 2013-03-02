#include "SDLRenderer.h"

#include <SDL.h>

#include "Sprite.h"
#include "Animation.h"

SDLRenderer::SDLRenderer():screen(NULL){}

SDLRenderer::~SDLRenderer(){}

void SDLRenderer::init(){
	screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(screen == NULL){
		fprintf(stderr, "Unable to create video window!");
	}
}

void SDLRenderer::uninit(){
	SDL_Quit();
}

void SDLRenderer::clear(){
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
}

void SDLRenderer::flip(){
	SDL_Flip(screen);
}

void SDLRenderer::drawAnimationFrame(const Vector2 &pos, int frame, Animation *anim){
	SDL_Rect srcRect = {
		0, 0,
		anim->getWidth(),
		anim->getHeight()
	};

	SDL_Rect dstRect = { pos[0], pos[1], 0, 0 };
	SDL_BlitSurface(anim->getFrame(frame), &srcRect, screen, &dstRect);
}