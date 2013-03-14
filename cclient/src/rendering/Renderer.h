#ifndef _RENDERER_H
#define _RENDERER_H

#include "../vector.h"
#include "../matrix.h"
#include "RenderContext.h"

class Sprite;
class Animation;
class Scene;

class SDL_Surface;

class Renderer {
public:
	Renderer();

	//Helper for drawing a full scene
	void drawScene(Scene *scene, const RenderContext &cxt);

	virtual void init(int screenWidth, int screenHeight) = 0;
	virtual void uninit() = 0;

	virtual void swapBuffer() = 0;

	virtual Vector2 getSize() const = 0;

	virtual void drawAnimationFrame(const Vector2 &pos, const Vector2 &size, int frame, Animation *anim, const RenderContext &cxt) = 0;
	virtual void fillRect(const Vector4 &bounds, const Vector4 &color, const RenderContext &cxt) = 0;
};



#endif