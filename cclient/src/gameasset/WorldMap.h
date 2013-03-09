#ifndef _WORLD_MAP_H
#define _WORLD_MAP_H

#include "GameAsset.h"

class Grid;

class WorldMap : public GameAsset {
public:
	virtual GameAssetType getType() const;

	void setMapGrid(Grid *grid);
	Grid *getMapGrid() const;

private:
	Grid *mapGrid;

};

#endif
