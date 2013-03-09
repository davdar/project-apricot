#include "WorldMap.h"

#include "../Grid.h"

GameAssetType WorldMap::getType() const { return GAME_ASSET_MAP; }

void WorldMap::setMapGrid(Grid *grid){ this->mapGrid = grid; }
Grid *WorldMap::getMapGrid() const { return mapGrid; }