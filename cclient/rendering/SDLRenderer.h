#ifndef _SDL_RENDERER_H
#define _SDL_RENDERER_H

#include "Renderer.h"

class SDL_Surface;

class SDLRenderer : public Renderer {
public:
	SDLRenderer(SDL_Surface *screen);

	virtual void drawSprite(Sprite *sprite);

private:
	SDL_Surface *screen;
};


#endif