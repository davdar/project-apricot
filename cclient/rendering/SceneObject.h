#ifndef _SCENE_OBJECT_H
#define _SCENE_OBJECT_H

#include <vector>

#include "../vector.h"

class Sprite;

class SceneObject {
public:
	SceneObject();
	SceneObject(Sprite *sprite, 
		const Vector2 &pos = Vector2(0,0), 
		const Vector2 &size = Vector2(1,1));

	const Vector2 &getPosition();
	void setPosition(const Vector2 &pos);

	const Vector2 &getSize();
	void setSize(const Vector2 &size);

	Sprite *getSprite();
	void setSprite(Sprite *sprite);

private:
	Vector2 position;
	Vector2 size;
	Sprite *sprite;
};

#endif