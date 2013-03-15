#include "SDLSurfaceAnimation.h"

#include <SDL.h>
#include <cassert>

#include "Animation.h"

const AnimationType SDLSurfaceAnimation::type = { "SDLSurfaceAnimation" };

SDLSurfaceAnimation::SDLSurfaceAnimation(int width, int height, int frameCount, SDL_Surface **frames)
:Animation(width,height,frameCount,&type)
,frames(frames)
{}

SDLSurfaceAnimation::~SDLSurfaceAnimation(){
	int frameCount = getFrameCount();
	for(int i = 0; i < frameCount; i++){
		delete frames[i];
	}

	delete [] frames;
}

SDL_Surface *SDLSurfaceAnimation::getFrame(int frameIndex) const { 
	assert(frameIndex >= 0);
	assert(frameIndex < getFrameCount());
	return frames[frameIndex];
}