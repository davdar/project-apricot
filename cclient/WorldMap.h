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

	virtual Vector2 getPosition() const;
	virtual Vector2 getSize() const;	

	virtual void draw(Renderer *renderer);

private:
	Grid *mapGrid;

};



#endif
