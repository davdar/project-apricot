#include "AnimationCatalog.h"

#include <SDL.h>
#include <SDL_image.h>

#include <algorithm>

#include "Animation.h"

AnimationCatalog *AnimationCatalog::singletonInstance = NULL;

AnimationCatalog *AnimationCatalog::instance(){
	if(singletonInstance == NULL){
		singletonInstance = new AnimationCatalog();
	}
	return singletonInstance;
}

AnimationCatalog::AnimationCatalog(){}

AnimationCatalog::~AnimationCatalog(){
	std::map<std::string, Animation*>::iterator iter;
	for(iter = animations.begin(); iter != animations.end(); iter++){
		delete (*iter).second;
	}
}

void AnimationCatalog::loadAnimation(const std::string &name, int frameCount, const std::string *filenames){
	SDL_Surface **frames = new SDL_Surface*[frameCount];

	int maxWidth;
	int maxHeight;

	for(int i = 0; i < frameCount; i++){
		frames[i] = IMG_Load(filenames[i].c_str());
		maxWidth = std::max(frames[i]->w, maxWidth);
		maxHeight = std::max(frames[i]->h, maxHeight);
	}

	Animation *anim = new Animation(maxWidth, maxHeight, frameCount, frames);
	animations[name] = anim;
}
