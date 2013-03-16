#include "AnimationSprite.h"

#include "Animation.h"
#include "Renderer.h"
#include "../geom.h"
#include "../types.h"
#include "../gamedata/GameData.h"

AnimationSprite::AnimationSprite(const Vector2 &position,
								const Vector2 &size,
								int frame,
								shared_ptr<Animation> animation,
								shared_ptr<GameData> gameData)
:position(position)
,size(size)
,frame(frame)
,animation(animation)
,gameData(gameData)
{}

Vector2 AnimationSprite::getPosition() const { return position; }
void AnimationSprite::setPosition(const Vector2 &position){ this->position = position; }

Vector2 AnimationSprite::getSize() const { return size; }
void AnimationSprite::setSize(const Vector2 &size){ this->size = size; }

shared_ptr<GameData> AnimationSprite::getGameData(){ return gameData; }

shared_ptr<Animation> AnimationSprite::getAnimation() const { return animation; }
void AnimationSprite::setAnimation(shared_ptr<Animation> animation){ this->animation = animation; }

int AnimationSprite::getFrame() const { return frame; }
void AnimationSprite::setFrame(int frame){ this->frame = frame; }

void AnimationSprite::draw(Renderer *renderer, const RenderContext &cxt){
	renderer->drawAnimationFrame(getPosition(), getSize(), getFrame(), getAnimation(), cxt);
}

