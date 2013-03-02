#ifndef _RENDERER_H
#define _RENDERER_H

#include "../vector.h"

class Sprite;
class Animation;
class Scene;

class Renderer {
public:
	Renderer();

	const Vector2 &getViewportPos();
	void setViewportPos(const Vector2 &pos);

	void renderScene(Scene *scene);

	virtual void init() = 0;
	virtual void uninit() = 0;

	virtual void clear() = 0;
	virtual void flip() = 0;

	virtual void drawAnimationFrame(const Vector2 &pos, int frame, Animation *anim) = 0;

private:
	Vector2 viewportPos;
};



#endif
