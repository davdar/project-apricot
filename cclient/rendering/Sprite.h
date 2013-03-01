#ifndef _SPRITE_H
#define _SPRITE_H

#include "../vector.h"

class Animation;
class SDL_Surface;

class Sprite {

public:
	Sprite();
	Sprite(const Sprite &sprite);
	~Sprite();

	void setTranslation(const Vector2 &in_translation);
	const Vector2 &getTranslation();

	/*
	 * TODO:To be implemented at some later date 
	 *
	void setScale(const Vector2 &scale);
	const Vector2 &getScale();

	void setRotation(double rotation);
	double getRotation();

	*
	*/

	void setAnimation(Animation *in_animation);
	Animation *getAnimation();

	void setCurrentFrame(int in_frame);
	int getCurrentFrame();

	SDL_Surface *getAnimationFrame();
	
private:
	Vector2 translation;

	/*
	 *
	Vector2 scale;
	double rotation;
	*
	*/

	Animation *animation;

	int currentFrame;
};











#endif

