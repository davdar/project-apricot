#include "WorldMap.h"

#include <SDL.h>
#include "Grid.h"

static const int MAP_GRID_CELL_WIDTH = 32;

void WorldMap::setMapGrid(Grid *grid){ this->mapGrid = grid; }
Grid *WorldMap::getMapGrid() const { return mapGrid; }

void WorldMap::draw(SDL_Surface *dst, SDL_Rect *dstRect) const {
	for(int gridX = 0; gridX < mapGrid->getWidth(); gridX++){
		for(int gridY = 0; gridY < mapGrid->getHeight(); gridY++){
			int color = SDL_MapRGB(dst->format, mapGrid->sample(gridX, gridY), 0, 0);
			SDL_Rect tileRect = {
				dstRect->x + gridX*MAP_GRID_CELL_WIDTH,
				dstRect->y + gridY*MAP_GRID_CELL_WIDTH,
				MAP_GRID_CELL_WIDTH,
				MAP_GRID_CELL_WIDTH
			};
			SDL_FillRect(dst, &tileRect, color);
		}
	}
}