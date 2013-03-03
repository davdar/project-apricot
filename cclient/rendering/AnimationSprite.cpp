#include "AnimationSprite.h"

#include <SDL.h>
#include "Animation.h"

AnimationSprite::AnimationSprite()
:animation(NULL),currentFrame(0)
{}

void AnimationSprite::setAnimation(Animation *in_animation){ animation = in_animation; }
Animation *AnimationSprite::getAnimation() const { return animation; }

void AnimationSprite::setCurrentFrame(int in_frame){ currentFrame = in_frame; }
int AnimationSprite::getCurrentFrame() const { return currentFrame; }

void AnimationSprite::draw(SDL_Surface *dst, SDL_Rect *dstRect) const {
	SDL_Surface *frame = getAnimation()->getFrame(getCurrentFrame());
	SDL_Rect frameRect = {
		0, 0,
		animation->getWidth(),
		animation->getHeight()
	};
	SDL_BlitSurface(frame, &frameRect, dst, dstRect);
}

