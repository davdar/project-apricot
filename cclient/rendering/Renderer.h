#ifndef _RENDERER_H
#define _RENDERER_H

#include "../vector.h"

class Sprite;
class Animation;
class Scene;

class SDL_Surface;

class Renderer {
public:
	Renderer();

	const Vector2 &getViewportPos();
	void setViewportPos(const Vector2 &pos);

	void drawScene(Scene *scene);

	virtual void swapBuffer() = 0;

	virtual void init(int screenWidth, int screenHeight) = 0;
	virtual void uninit() = 0;

	virtual void drawAnimationFrame(const Vector2 &pos, const Vector2 &size, int frame, Animation *anim) = 0;

	virtual void fillRect(const Vector4 &bounds, const Vector4 &color) = 0;

private:
	Vector2 viewportPos;
};



#endif
