#ifndef _WORLD_MAP_SPRITE
#define _WORLD_MAP_SPRITE

#include "../rendering/Sprite.h"

class WorldMap;

class WorldMapSprite : public Sprite {
public:
	WorldMapSprite(int gridCellPixelWidth, WorldMap *worldMap);

	virtual Vector2 getPosition() const;
	virtual Vector2 getSize() const;

	//Return the game asset that this sprite represents
	virtual GameAsset *getGameAsset();

	virtual void draw(Renderer *renderer);

	//Test whether the given point intersects this sprite
	virtual bool hit(const Vector2 &pos) const;


private:
	int gridCellPixelWidth;
	WorldMap *worldMap;
};


#endif