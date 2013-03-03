#ifndef _ANIMATION_SPRITE_H
#define _ANIMATION_SPRITE_H

#include "Sprite.h"

class Animation;

class AnimationSprite : public Sprite {
public:
	AnimationSprite();

	void setAnimation(Animation *in_animation);
	Animation *getAnimation() const;

	void setCurrentFrame(int in_frame);
	int getCurrentFrame() const;

	virtual void draw(SDL_Surface *dst, SDL_Rect *dstRect) const;

private:
	Animation *animation;

	int currentFrame;
};

#endif