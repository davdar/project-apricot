#include "Animation.h"

#include <SDL.h>
#include <memory>

Animation::Animation(int width, int height, int frameCount, const AnimationType *type)
:width(width),height(height),frameCount(frameCount),instanceType(type)
{}

Animation::~Animation(){

}

int Animation::getWidth() const { return width; }
int Animation::getHeight() const { return height; }
int Animation::getFrameCount() const { return frameCount; }
const AnimationType *Animation::getType() const { return instanceType; }

