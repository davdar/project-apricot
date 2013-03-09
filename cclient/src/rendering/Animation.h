#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <cassert>

class SDL_Surface;

/*
 * class Animation
 *
 * Data object for holding animation information
 *
 */

class Animation {
public:
	// Takes ownership of 'frames'
	Animation(int width, int height, int frameCount, SDL_Surface **frames);
	~Animation();

	int getWidth();
	int getHeight();
	int getFrameCount();

	SDL_Surface *getFrame(int frameIndex);

private:
	//Prevent default copy-constructor from being created
	Animation(const Animation &anim){ assert(false); }

	int width;
	int height;
	int frameCount;

	//TODO: This should probably be made to use tiles on a single SDL_Surface at some point
	SDL_Surface **frames;


};

#endif
