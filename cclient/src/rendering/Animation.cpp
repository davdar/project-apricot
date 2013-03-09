#include "Animation.h"

#include <SDL.h>
#include <memory>

Animation::Animation(int width, int height, int frameCount, SDL_Surface **frames)
:width(width),height(height),frameCount(frameCount),frames(frames)
{}

Animation::~Animation(){
	for(int i = 0; i < frameCount; i++){
		delete frames[i];
	}

	delete [] frames;
}

int Animation::getWidth(){ return width; }
int Animation::getHeight(){ return height; }
int Animation::getFrameCount(){ return frameCount; }
SDL_Surface *Animation::getFrame(int frameIndex){ 
	assert(frameIndex >= 0);
	assert(frameIndex < frameCount);
	return frames[frameIndex];
}
