#ifndef _SDL_SURFACE_ANIMATION_H
#define _SDL_SURFACE_ANIMATION_H

#include "Animation.h"

class SDL_Surface;

class SDLSurfaceAnimation : public Animation {
public:
	static const AnimationType type;

public:
	//Takes ownership of 'frames'
	SDLSurfaceAnimation(int width, int height, int frameCount, SDL_Surface **frames);
	~SDLSurfaceAnimation();

	SDL_Surface *getFrame(int frameIndex) const;

private:
	SDL_Surface **frames;

};



#endif
