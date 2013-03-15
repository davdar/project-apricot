#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <cassert>
#include <set>


class SDL_Surface;

/*
 * class Animation
 *
 * Data object for holding animation information
 *
 */


struct AnimationType {
	const char *name;
};

class Animation {
public:
	Animation(int width, int height, int frameCount, const AnimationType *type);
	
	~Animation();

	int getWidth() const;
	int getHeight() const;
	int getFrameCount() const;

	const AnimationType *getType() const;

private:
	int width;
	int height;
	int frameCount;
	const AnimationType *instanceType;

private:
	static std::set<const char*> registeredTypes;
};

#endif
