#include "AnimationSprite.h"

#include "Animation.h"
#include "Renderer.h"
#include "../geom.h"
#include "../gameasset/GameAsset.h"

AnimationSprite::AnimationSprite(const Vector2 &position,
								const Vector2 &size,
								int frame,
								Animation *animation,
								GameAsset *gameAsset)
:position(position)
,size(size)
,frame(frame)
,animation(animation)
,gameAsset(gameAsset)
{}

Vector2 AnimationSprite::getPosition() const { return position; }
void AnimationSprite::setPosition(const Vector2 &position){ this->position = position; }

Vector2 AnimationSprite::getSize() const { return size; }
void AnimationSprite::setSize(const Vector2 &size){ this->size = size; }

GameAsset *AnimationSprite::getGameAsset(){ return gameAsset; }

Animation *AnimationSprite::getAnimation() const { return animation; }
void AnimationSprite::setAnimation(Animation *animation){ this->animation = animation; }

int AnimationSprite::getFrame() const { return frame; }
void AnimationSprite::setFrame(int frame){ this->frame = frame; }

void AnimationSprite::draw(Renderer *renderer){
	renderer->drawAnimationFrame(getPosition(), getSize(), getFrame(), getAnimation());
}

bool AnimationSprite::hit(const Vector2 &pos) const {
	return geom::intersectPointRect(pos, getPosition(), getPosition()+getSize());
}

