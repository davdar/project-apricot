#ifndef _SDL_RENDERER_H
#define _SDL_RENDERER_H

#include "Renderer.h"

class SDL_Surface;

class SDLRenderer : public Renderer {
public:
	SDLRenderer();
	~SDLRenderer();

	virtual void init();
	virtual void uninit();

	virtual void clear();
	virtual void flip();
	virtual void drawAnimationFrame(const Vector2 &pos, int frame, Animation *anim);

private:
	SDL_Surface *screen;
};


#endif