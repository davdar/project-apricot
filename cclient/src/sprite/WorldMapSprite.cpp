#include "WorldMapSprite.h"

#include "../vector.h"
#include "../gamedata/WorldMap.h"
#include "../Grid.h"
#include "../rendering/Renderer.h"

WorldMapSprite::WorldMapSprite(int gridCellPixelWidth, shared_ptr<WorldMap> worldMap)
:gridCellPixelWidth(gridCellPixelWidth)
,worldMap(worldMap)
{}

Vector2 WorldMapSprite::getPosition() const { return Vector2(0,0); }
Vector2 WorldMapSprite::getSize() const { 
	int pixelWidth = gridCellPixelWidth * worldMap->getMapGrid()->getWidth();
	int pixelHeight = gridCellPixelWidth * worldMap->getMapGrid()->getHeight();
	return Vector2(pixelWidth, pixelHeight);
}

shared_ptr<GameData> WorldMapSprite::getGameData(){ return worldMap; }

void WorldMapSprite::draw(Renderer *renderer, const RenderContext &cxt){
	Grid *grid = worldMap->getMapGrid();

	for(int gridX = 0; gridX < grid->getWidth(); gridX++){
		for(int gridY = 0; gridY < grid->getHeight(); gridY++){
			Vector4 color(grid->sample(gridX, gridY), 0, 0, 1.0);
			Vector4 tileBounds(
				gridX*gridCellPixelWidth,
				gridY*gridCellPixelWidth,
				gridCellPixelWidth,
				gridCellPixelWidth
			);	
			renderer->fillRect(tileBounds, color, cxt);
		}
	}
}

bool WorldMapSprite::hit(const Vector2 &pos) const {
	Vector2 size = getSize();
	return pos[0] >= 0 && pos[0] < size[0]
			&& pos[1] >= 0 && pos[1] < size[1];
}

