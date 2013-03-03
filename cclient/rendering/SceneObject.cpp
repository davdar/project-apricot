#include "SceneObject.h"

#include "Sprite.h"

SceneObject::SceneObject():sprite(NULL),position(0,0){}

SceneObject::SceneObject(Sprite *sprite, const Vector2 &position, const Vector2 &size)
:sprite(sprite),position(position),size(size)
{}

const Vector2 &SceneObject::getPosition(){ return position; }
void SceneObject::setPosition(const Vector2 &position){ this->position = position; }

Sprite *SceneObject::getSprite(){ return sprite; }
void SceneObject::setSprite(Sprite *sprite){ this->sprite = sprite; }

const Vector2 &SceneObject::getSize(){ return size; }
void setSize(const Vector2 &size);
