#ifndef _SCENE_H
#define _SCENE_H

#include <vector>
#include <map>
#include "../vector.h"

class Sprite;

typedef std::vector<shared_ptr<Sprite>> SceneLayer;

/*
 * A Scene represents a configuration of objects that
 * can be rendered to the screen.
 */
class Scene {
public:
	Scene(const Vector2 &size);

	const Vector2 &getSize() const;
	void setSize(const Vector2 &size);

	std::map<int, SceneLayer> &getLayers();
	const std::map<int, SceneLayer> &getLayers() const;

	shared_ptr<Sprite> pickSprite(const Vector2 &pos);

private:
	//Size in pixels
	Vector2 size;

	std::map<int, SceneLayer> layers;
};


#endif
