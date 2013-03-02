#include "Renderer.h"

#include <map>

#include "Sprite.h"
#include "Scene.h"

Renderer::Renderer():viewportPos(0,0){}

const Vector2 &Renderer::getViewportPos(){ return viewportPos; }

void Renderer::setViewportPos(const Vector2 &viewportPos){ this->viewportPos = viewportPos; }

void Renderer::renderScene(Scene *scene){
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