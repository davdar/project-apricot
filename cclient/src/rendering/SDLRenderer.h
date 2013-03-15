#ifndef _SDL_RENDERER_H
#define _SDL_RENDERER_H

#include "Renderer.h"
#include "RenderContext.h"
#include "../types.h"

class SDL_Surface;

class SDLRenderer : public Renderer {
public:
	SDLRenderer();
	~SDLRenderer();

	virtual void init(int screenWidth, int screenHeight);
	virtual void uninit();

	virtual void swapBuffer();

	virtual Vector2 getSize() const;

	virtual shared_ptr<Animation> loadAnimation(const char *assetName);

	virtual void drawAnimationFrame(const Vector2 &pos, const Vector2 &size, int frame, shared_ptr<Animation> anim, const RenderContext &cxt);
	virtual void fillRect(const Vector4 &bounds, const Vector4 &color, const RenderContext &cxt);

private:
	SDL_Surface *screen;
};


#endif
