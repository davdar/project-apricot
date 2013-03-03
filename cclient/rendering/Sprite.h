#ifndef _SPRITE_H
#define _SPRITE_H

#include "../vector.h"

class Animation;
class SDL_Surface;
class SDL_Rect;
class Renderer;

/*
 * class Sprite - Represents a drawable object on the screen
 */
class Sprite {

public:
	virtual void draw(SDL_Surface *dst, SDL_Rect *dstRect) const = 0;

	//Here we could possibly also add
	//hit(Vector2 pos)
	//getOwner() //i.e. to get back to the character/player/etc. this sprite represents
};



#endif

