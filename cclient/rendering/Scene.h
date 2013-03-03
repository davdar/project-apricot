#ifndef _SCENE_H
#define _SCENE_H

#include <vector>
#include <map>

class SceneObject;

typedef std::vector<SceneObject*> SceneLayer;

/*
 * A Scene represents a configuration of objects that
 * can be rendered to the screen.
 */
class Scene {
public:
	Scene(const Vector2 &size):size(size){}

	const Vector2 &getSize(){ return size; }
	void setSize(const Vector2 &size){ this->size = size; }

	std::map<int, SceneLayer> &getLayers(){ return layers; }

private:
	//Size in pixels
	Vector2 size;

	std::map<int, SceneLayer> layers;
};


#endif