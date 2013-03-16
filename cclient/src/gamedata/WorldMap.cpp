#include "WorldMap.h"

#include "../Grid.h"

WorldMap::WorldMap():GameData(type){}

void WorldMap::setMapGrid(Grid *grid){ this->mapGrid = grid; }
Grid *WorldMap::getMapGrid() const { return mapGrid; }