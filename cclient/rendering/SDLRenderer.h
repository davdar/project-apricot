#ifndef _SDL_RENDERER_H
#define _SDL_RENDERER_H

#include "Renderer.h"

class SDL_Surface;

class SDLRenderer : public Renderer {
public:
	SDLRenderer();
	~SDLRenderer();

	virtual void init(int screenWidth, int screenHeight);
	virtual void uninit();

	virtual void swapBuffer();

	virtual void drawAnimationFrame(const Vector2 &pos, const Vector2 &size, int frame, Animation *anim);

	virtual void fillRect(const Vector4 &bounds, const Vector4 &color);

private:
	SDL_Surface *screen;
};


#endif
