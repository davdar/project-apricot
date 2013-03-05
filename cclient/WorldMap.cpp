#include "WorldMap.h"

#include "Grid.h"

#include "vector.h"
#include "rendering/Renderer.h"

static const int MAP_GRID_CELL_WIDTH = 32;

Vector2 WorldMap::getPosition() const { return Vector2(0,0); }
Vector2 WorldMap::getSize() const { 
	int width = mapGrid->getWidth()*MAP_GRID_CELL_WIDTH;
	int height = mapGrid->getHeight()*MAP_GRID_CELL_WIDTH;
	return Vector2(width, height);
}

void WorldMap::setMapGrid(Grid *grid){ this->mapGrid = grid; }
Grid *WorldMap::getMapGrid() const { return mapGrid; }

void WorldMap::draw(Renderer *renderer) {
	for(int gridX = 0; gridX < mapGrid->getWidth(); gridX++){
		for(int gridY = 0; gridY < mapGrid->getHeight(); gridY++){
			Vector4 color(mapGrid->sample(gridX, gridY), 0, 0, 1.0);
			Vector4 tileBounds(
				gridX*MAP_GRID_CELL_WIDTH,
				gridY*MAP_GRID_CELL_WIDTH,
				MAP_GRID_CELL_WIDTH,
				MAP_GRID_CELL_WIDTH
			);	
			renderer->fillRect(tileBounds, color);
		}
	}
}
