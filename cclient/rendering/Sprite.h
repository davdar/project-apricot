#ifndef _SPRITE_H
#define _SPRITE_H

#include "../vector.h"

class Animation;
class Renderer;

/*
 * class Sprite - Represents a drawable object on the screen
 */
class Sprite {

public:
	virtual Vector2 getPosition() const = 0;
	virtual Vector2 getSize() const = 0;

	virtual void draw(Renderer *renderer) = 0;

	//Here we could possibly also add
	//hit(Vector2 pos)
	//getGameAsset() //i.e. to get back to the character/player/etc. this sprite represents
};




#endif

