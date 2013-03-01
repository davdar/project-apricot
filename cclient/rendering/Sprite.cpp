#include "Sprite.h"

#include "SDL.h"
#include "Animation.h"

Sprite::Sprite()
:translation(0,0)
,animation(NULL)
,currentFrame(0)
{}

Sprite::Sprite(const Sprite &sprite)
:translation(sprite.translation) 
,animation(sprite.animation)
,currentFrame(sprite.currentFrame)
{}

Sprite::~Sprite(){}

void Sprite::setTranslation(const Vector2 &in_translation){ translation = in_translation; }

const Vector2 &Sprite::getTranslation(){ return translation; }


void Sprite::setAnimation(Animation *in_animation){ animation = in_animation; }
Animation *Sprite::getAnimation(){ return animation; }

void Sprite::setCurrentFrame(int in_frame){ currentFrame = in_frame; }
int Sprite::getCurrentFrame(){ return currentFrame; }

SDL_Surface *Sprite::getAnimationFrame(){
	return getAnimation()->getFrame(getCurrentFrame());
}