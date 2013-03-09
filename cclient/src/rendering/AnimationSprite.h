#ifndef _ANIMATION_SPRITE_H
#define _ANIMATION_SPRITE_H

#include "Sprite.h"

class Animation;

/*
 * A generic animation sprite
 */
class AnimationSprite : public Sprite {
public:
	AnimationSprite(const Vector2 &position, const Vector2 &size, int frame, Animation *animation, GameAsset *gameAsset);

	virtual Vector2 getPosition() const;
	void setPosition(const Vector2 &pos);

	virtual Vector2 getSize() const;
	void setSize(const Vector2 &size);

	virtual GameAsset *getGameAsset();

	Animation *getAnimation() const;
	void setAnimation(Animation *animation);
	
	int getFrame() const;
	void setFrame(int frame);

	virtual void draw(Renderer *renderer);

	virtual bool hit(const Vector2 &pos) const;
	
private:
	Vector2 position;
	Vector2 size;
	Animation *animation;
	GameAsset *gameAsset;
	int frame;
};

#endif
