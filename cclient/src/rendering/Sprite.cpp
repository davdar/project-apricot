#include "Sprite.h"

// Provide a default implementation that simply checks if
// the point is within the bounding box of the sprite
bool Sprite::hit(const Vector2 &pos) const {
	Vector2 spriteMin = getPosition();
	Vector2 spriteMax = spriteMin + getSize();
	return pos[0] >= spriteMin[0] &&
		pos[0] < spriteMax[0] &&
		pos[1] >= spriteMin[1] &&
		pos[1] < spriteMax[1];
}

