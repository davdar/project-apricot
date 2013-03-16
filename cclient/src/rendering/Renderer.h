#ifndef _RENDERER_H
#define _RENDERER_H

#include "../types.h"
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
	void drawScene(const Scene *scene, const RenderContext &cxt);
	
	virtual void init(int screenWidth, int screenHeight) = 0;
	virtual void uninit() = 0;

	virtual void swapBuffer() = 0;

	virtual Vector2 getSize() const = 0;

	virtual shared_ptr<Animation> loadAnimation(const char *assetName) = 0;

	virtual void drawAnimationFrame(const Vector2 &pos, const Vector2 &size, int frame, shared_ptr<Animation> anim, const RenderContext &cxt) = 0;
	virtual void fillRect(const Vector4 &bounds, const Vector4 &color, const RenderContext &cxt) = 0;
};



#endif
