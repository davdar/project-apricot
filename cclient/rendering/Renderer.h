#ifndef _RENDERER_H
#define _RENDERER_H

#include "../vector.h"

class Sprite;
class Animation;
class Scene;

class SDL_Surface;

class Renderer {
public:
	Renderer(SDL_Surface *screen);

	const Vector2 &getViewportPos();
	void setViewportPos(const Vector2 &pos);

	void drawScene(Scene *scene);

	void drawAnimationFrame(const Vector2 &pos, int frame, Animation *anim);

private:
	Vector2 viewportPos;
	SDL_Surface *screen;
};



#endif
