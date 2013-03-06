#include "SDLRenderer.h"

#include <cstdlib>
#include <SDL.h>

#include "Sprite.h"
#include "Animation.h"

SDLRenderer::SDLRenderer():screen(NULL){}

SDLRenderer::~SDLRenderer(){}

void SDLRenderer::init(int screenWidth, int screenHeight){
	screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(screen == NULL){
		fprintf(stderr, "Unable to create video window!");
	}
}

void SDLRenderer::uninit(){
	SDL_Quit();
}

void SDLRenderer::swapBuffer(){
	SDL_Flip(screen);
}


void SDLRenderer::drawAnimationFrame(const Vector2 &pos, const Vector2 &size, int frame, Animation *anim){
	Vector3 transformedPos = getTransform() * Vector3(pos[0], pos[1], 1);
	
	//TODO: At some point we could try scaling the animation to the 'size' parameter
	SDL_Rect srcRect = {
		0, 0,
		anim->getWidth(),
		anim->getHeight()
	};

	SDL_Rect dstRect = { transformedPos[0], transformedPos[1], size[0], size[1] };
	SDL_BlitSurface(anim->getFrame(frame), &srcRect, screen, &dstRect);
}

void SDLRenderer::fillRect(const Vector4 &bounds, const Vector4 &color){
	Vector3 transformedPos = getTransform() * Vector3(bounds[0], bounds[1], 1);
	Vector3 transformedSize = getTransform() * Vector3(bounds[2], bounds[3], 0);
	SDL_Rect dstRect = {
		transformedPos[0], transformedPos[1], 
		transformedSize[0], transformedSize[1]
	};
	int mappedColor = SDL_MapRGBA(screen->format, color[0], color[1], color[2], color[3]);
	SDL_FillRect(screen, &dstRect, mappedColor);
}

