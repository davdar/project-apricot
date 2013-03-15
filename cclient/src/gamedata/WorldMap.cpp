#include "WorldMap.h"

#include "../Grid.h"

GameDataType WorldMap::getType() const { return GAME_DATA_MAP; }

void WorldMap::setMapGrid(Grid *grid){ this->mapGrid = grid; }
Grid *WorldMap::getMapGrid() const { return mapGrid; }