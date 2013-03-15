#ifndef _WORLD_MAP_SPRITE
#define _WORLD_MAP_SPRITE

#include "../types.h"
#include "../rendering/Sprite.h"
#include "../rendering/RenderContext.h"

class WorldMap;
class GameData;

class WorldMapSprite : public Sprite {
public:
	WorldMapSprite(int gridCellPixelWidth, shared_ptr<WorldMap> worldMap);

	virtual Vector2 getPosition() const;
	virtual Vector2 getSize() const;

	//Return the game asset that this sprite represents
	virtual shared_ptr<GameData> getGameData();

	virtual void draw(Renderer *renderer, const RenderContext &cxt);

	//Test whether the given point intersects this sprite
	virtual bool hit(const Vector2 &pos) const;


private:
	int gridCellPixelWidth;
	shared_ptr<WorldMap> worldMap;
};


#endif