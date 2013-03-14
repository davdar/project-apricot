#ifndef _RENDER_CONTEXT_H
#define _RENDER_CONTEXT_H

#include "../matrix.h"

struct RenderContext {
	Vector2 viewportPos;

	Matrix3x3 getTransform() const;
};


// Inline function implementations

inline Matrix3x3 RenderContext::getTransform() const {
	return Matrix3x3(1, 0, -viewportPos[0],
					 0, 1, -viewportPos[1],
					 0, 1, 1);
}

#endif