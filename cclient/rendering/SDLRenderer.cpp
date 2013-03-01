#include "SDLRenderer.h"

#include <SDL.h>

#include "Sprite.h"
#include "Animation.h"

SDLRenderer::SDLRenderer(SDL_Surface *screen):screen(screen){

}

void SDLRenderer::drawSprite(Sprite* sprite){
	SDL_Rect srcRect = {
		0, 0,
		sprite->getAnimation()->getWidth(),
		sprite->getAnimation()->getHeight()
	};
	SDL_Rect dstRect = {
		sprite->getTranslation()[0],
		sprite->getTranslation()[1],
		0, 0
	};
	SDL_BlitSurface(sprite->getAnimationFrame(), &srcRect, screen, &dstRect);
}