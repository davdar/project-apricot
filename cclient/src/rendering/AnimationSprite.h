#ifndef _ANIMATION_SPRITE_H
#define _ANIMATION_SPRITE_H

#include "../types.h"
#include "Sprite.h"
#include "RenderContext.h"

class Animation;
class GameData;

/*
 * A generic animation sprite
 */
class AnimationSprite : public Sprite {
public:
	AnimationSprite(const Vector2 &position, const Vector2 &size, int frame, shared_ptr<Animation> animation, shared_ptr<GameData> gameData);

	virtual Vector2 getPosition() const;
	void setPosition(const Vector2 &pos);

	virtual Vector2 getSize() const;
	void setSize(const Vector2 &size);

	virtual shared_ptr<GameData> getGameData();

	shared_ptr<Animation> getAnimation() const;
	void setAnimation(shared_ptr<Animation> animation);
	
	int getFrame() const;
	void setFrame(int frame);

	virtual void draw(Renderer *renderer, const RenderContext &cxt);
	
private:
	Vector2 position;
	Vector2 size;
	shared_ptr<Animation> animation;
	shared_ptr<GameData> gameData;
	int frame;
};

#endif
