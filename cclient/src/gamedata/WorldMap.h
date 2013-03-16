#ifndef _WORLD_MAP_H
#define _WORLD_MAP_H

#include "GameData.h"

class Grid;

class WorldMap : public GameData {
public:
	static const GameDataType type = GAME_DATA_MAP;

public:
	WorldMap();

	void setMapGrid(Grid *grid);
	Grid *getMapGrid() const;

private:
	Grid *mapGrid;

};

#endif
