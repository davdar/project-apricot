#ifndef _WORLD_MAP_H
#define _WORLD_MAP_H

#include "rendering/Sprite.h"

class Grid;
class SDL_Surface;
class SDL_Rect;

class WorldMap : public Sprite {
public:
	void setMapGrid(Grid *grid);
	Grid *getMapGrid() const;

	virtual void draw(SDL_Surface *dst, SDL_Rect *dstRect) const;

private:
	Grid *mapGrid;

};



#endif