#include "Scene.h"

#include "Sprite.h"

Scene::Scene(const Vector2 &size):size(size){}

const Vector2 &Scene::getSize() const { return size; }
void Scene::setSize(const Vector2 &size){ this->size = size; }

std::map<int, SceneLayer> &Scene::getLayers(){ return layers; }
const std::map<int, SceneLayer> &Scene::getLayers() const { return layers; }


// TOOO: Do something more efficient than looping through every sprite
// (Or is this good enough?)
shared_ptr<Sprite> Scene::pickSprite(const Vector2 &pos){
	std::map<int, SceneLayer>::reverse_iterator layerIter;
	for(layerIter = layers.rbegin(); layerIter != layers.rend(); layerIter++){
		SceneLayer layer = (*layerIter).second;
		SceneLayer::reverse_iterator spriteIter;
		for(spriteIter = layer.rbegin(); spriteIter != layer.rend(); spriteIter++){
			if((*spriteIter)->hit(pos)){
				return (*spriteIter);
			}
		}
	}
	return shared_ptr<Sprite>();
}