#include "Renderer.h"

#include <SDL.h>
#include <map>

#include "Sprite.h"
#include "Scene.h"
#include "Animation.h"

Renderer::Renderer()
:viewportPos(0,0)
{}

const Vector2 &Renderer::getViewportPos(){ return viewportPos; }

void Renderer::setViewportPos(const Vector2 &viewportPos){ this->viewportPos = viewportPos; }

void Renderer::drawScene(Scene *scene){
	std::map<int, SceneLayer> layers = scene->getLayers();
	std::map<int, SceneLayer>::iterator iter;
	for(iter = layers.begin(); iter != layers.end(); iter++){
		SceneLayer layer = (*iter).second;
		SceneLayer::iterator spriteIter;
		for(spriteIter = layer.begin(); spriteIter != layer.end(); spriteIter++){
			Sprite *sprite = (*spriteIter);
			Vector2 relativePos = sprite->getPosition() - getViewportPos();
			Vector2 size = sprite->getSize();
			SDL_Rect drawRect = {
				relativePos[0], relativePos[1],
				size[0], size[1]
			};
			sprite->draw(this);
		}
	}
}
