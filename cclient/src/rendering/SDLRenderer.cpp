#include "SDLRenderer.h"

#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>

#include "Sprite.h"
#include "Animation.h"
#include "SDLSurfaceAnimation.h"

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

Vector2 SDLRenderer::getSize() const {
	return Vector2(screen->w, screen->h);
}

shared_ptr<Animation> SDLRenderer::loadAnimation(const char *assetName){
	//Currently we only support single-frame animations
	SDL_Surface *surf = IMG_Load(assetName);
	if ( !surf )
	{
		//TODO: Error logging?
		printf ( "IMG_Load: %s\n", IMG_GetError () );
		surf = SDL_CreateRGBSurface(SDL_SWSURFACE, 32, 32, 32, 0, 0, 0, 0);
	}
	SDL_Surface **frames = new SDL_Surface*[1];
	frames[0] = surf;
	return shared_ptr<Animation>(new SDLSurfaceAnimation(surf->w, surf->h, 1, frames));
}

void SDLRenderer::drawAnimationFrame(const Vector2 &pos, const Vector2 &size, int frame, shared_ptr<Animation> anim, const RenderContext &cxt){
	if(anim->getType() != &SDLSurfaceAnimation::type){
		//TODO: Return error code???
		return;
	}
	
	Vector3 transformedPos = cxt.getTransform() * Vector3(pos[0], pos[1], 1);
	
	//TODO: At some point we could try scaling the animation to the 'size' parameter
	SDL_Rect srcRect = {
		0, 0,
		anim->getWidth(),
		anim->getHeight()
	};

	SDL_Rect dstRect = { transformedPos[0], transformedPos[1], size[0], size[1] };
	SDL_BlitSurface(static_pointer_cast<SDLSurfaceAnimation>(anim)->getFrame(frame), &srcRect, screen, &dstRect);
}

void SDLRenderer::fillRect(const Vector4 &bounds, const Vector4 &color, const RenderContext &cxt){
	Matrix3x3 transform = cxt.getTransform();
	Vector3 transformedPos = transform * Vector3(bounds[0], bounds[1], 1);
	Vector3 transformedSize = transform * Vector3(bounds[2], bounds[3], 0);
	SDL_Rect dstRect = {
		transformedPos[0], transformedPos[1], 
		transformedSize[0], transformedSize[1]
	};
	int mappedColor = SDL_MapRGBA(screen->format, color[0], color[1], color[2], color[3]);
	SDL_FillRect(screen, &dstRect, mappedColor);
}

