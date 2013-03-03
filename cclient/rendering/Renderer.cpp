#include "Renderer.h"

#include <SDL.h>
#include <map>

#include "Sprite.h"
#include "Scene.h"
#include "SceneObject.h"
#include "Animation.h"

Renderer::Renderer(SDL_Surface *screen)
:screen(screen),viewportPos(0,0)
{}

const Vector2 &Renderer::getViewportPos(){ return viewportPos; }

void Renderer::setViewportPos(const Vector2 &viewportPos){ this->viewportPos = viewportPos; }

void Renderer::drawScene(Scene *scene){
	std::map<int, SceneLayer> layers = scene->getLayers();
	std::map<int, SceneLayer>::iterator iter;
	for(iter = layers.begin(); iter != layers.end(); iter++){
		SceneLayer layer = (*iter).second;
		SceneLayer::iterator sceneObjectIter;
		for(sceneObjectIter = layer.begin(); sceneObjectIter != layer.end(); sceneObjectIter++){
			SceneObject *sceneObject = (*sceneObjectIter);
			Vector2 relativePos = sceneObject->getPosition() - getViewportPos();
			Vector2 size = sceneObject->getSize();
			SDL_Rect drawRect = {
				relativePos[0], relativePos[1],
				size[0], size[1]
			};
			sceneObject->getSprite()->draw(screen, &drawRect);
		}
	}
}