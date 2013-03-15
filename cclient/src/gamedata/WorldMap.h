#ifndef _WORLD_MAP_H
#define _WORLD_MAP_H

#include "GameData.h"

class Grid;

class WorldMap : public GameData {
public:
	virtual GameDataType getType() const;

	void setMapGrid(Grid *grid);
	Grid *getMapGrid() const;

private:
	Grid *mapGrid;

};

#endif
