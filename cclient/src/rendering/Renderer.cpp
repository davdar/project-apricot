#include "Renderer.h"

#include <SDL.h>
#include <map>

#include "Sprite.h"
#include "Scene.h"
#include "Animation.h"

Renderer::Renderer(){}

void Renderer::drawScene(const Scene *scene, const RenderContext &cxt){
	std::map<int, SceneLayer> layers = scene->getLayers();
	std::map<int, SceneLayer>::iterator iter;
	for(iter = layers.begin(); iter != layers.end(); iter++){
		SceneLayer layer = (*iter).second;
		SceneLayer::iterator spriteIter;
		for(spriteIter = layer.begin(); spriteIter != layer.end(); spriteIter++){
			(*spriteIter)->draw(this, cxt);
		}
	}
}
