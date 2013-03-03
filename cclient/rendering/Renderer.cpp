#include "Renderer.h"

#include <SDL.h>
#include <map>

#include "Sprite.h"
#include "Scene.h"
#include "Animation.h"

Renderer::Renderer(SDL_Surface *screen)
:screen(screen),viewportPos(0,0)
{}

const Vector2 &Renderer::getViewportPos(){ return viewportPos; }

void Renderer::setViewportPos(const Vector2 &viewportPos){ this->viewportPos = viewportPos; }

void Renderer::drawAnimationFrame(const Vector2 &pos, int frame, Animation *anim){
	SDL_Rect srcRect = {
		0, 0,
		anim->getWidth(),
		anim->getHeight()
	};

	SDL_Rect dstRect = { pos[0], pos[1], 0, 0 };
	SDL_BlitSurface(anim->getFrame(frame), &srcRect, screen, &dstRect);
}

void Renderer::drawScene(Scene *scene){
	std::map<int, SceneLayer> layers = scene->getLayers();
	std::map<int, SceneLayer>::reverse_iterator iter;
	for(iter = layers.rbegin(); iter != layers.rend(); iter++){
		SceneLayer layer = (*iter).second;
		SceneLayer::iterator spriteIter;
		for(spriteIter = layer.begin(); spriteIter != layer.end(); spriteIter++){
			Sprite *sprite = (*spriteIter);
			Vector2 relativeSpritePos = sprite->getTranslation() - getViewportPos();
			drawAnimationFrame(relativeSpritePos, sprite->getCurrentFrame(), sprite->getAnimation());
		}
	}
}