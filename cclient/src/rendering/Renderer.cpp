#include "Renderer.h"

#include <SDL.h>
#include <map>

#include "Sprite.h"
#include "Scene.h"
#include "Animation.h"

Renderer::Renderer()
:viewportPos(0,0)
{}

const Vector2 &Renderer::getViewportPos() const { return viewportPos; }
void Renderer::setViewportPos(const Vector2 &viewportPos){ this->viewportPos = viewportPos; }

const Matrix3x3 &Renderer::getTransform() const { return transform; }
void Renderer::setTransform(const Matrix3x3 &transform){ this->transform = transform; }

Matrix3x3 Renderer::getDefaultTransform() const {
	return Matrix3x3(1, 0, -viewportPos[0],
					 0, 1, -viewportPos[1],
					 0, 1, 1);
}

void Renderer::drawScene(Scene *scene){
	std::map<int, SceneLayer> layers = scene->getLayers();
	std::map<int, SceneLayer>::iterator iter;
	for(iter = layers.begin(); iter != layers.end(); iter++){
		SceneLayer layer = (*iter).second;
		SceneLayer::iterator spriteIter;
		for(spriteIter = layer.begin(); spriteIter != layer.end(); spriteIter++){
			(*spriteIter)->draw(this);
		}
	}
}
