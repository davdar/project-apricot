#ifndef _GEOM_H
#define _GEOM_H

#include "vector.h"

namespace geom {

	inline bool intersectPointRect(const Vector2 &point, const Vector2 &rectP1, const Vector2 &rectP2){
		return point[0] >= rectP1[0] &&
				point[0] < rectP2[0] &&
				point[1] < rectP1[1] &&
				point[1] < rectP2[1];
	}
}



#endif