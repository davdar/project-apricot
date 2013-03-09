#ifndef _SPRITE_H
#define _SPRITE_H

#include "../vector.h"

class Animation;
class Renderer;
class GameAsset;

/*
 * class Sprite - Represents a drawable object on the screen
 */
class Sprite {

public:
	virtual Vector2 getPosition() const = 0;
	virtual Vector2 getSize() const = 0;

	virtual void draw(Renderer *renderer) = 0;

	//Test whether the given point intersects this sprite
	virtual bool hit(const Vector2 &pos) const = 0;

	//Return the game asset that this sprite represents
	virtual GameAsset *getGameAsset() = 0;
};




#endif

