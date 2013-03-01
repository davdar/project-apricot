#ifndef _RENDERER_H
#define _RENDERER_H

class Sprite;

class Renderer {
public:

	virtual void drawSprite(Sprite *sprite) = 0;
};


#endif
