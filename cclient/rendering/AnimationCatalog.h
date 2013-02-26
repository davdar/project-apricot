#ifndef _ANIMATION_CATALOG_H
#define _ANIMATION_CATALOG_H

#include <cassert>
#include <string>
#include <map>

class Animation;

class AnimationCatalog {

public:
	static AnimationCatalog *instance();

	void loadAnimation(const std::string &name, int frameCount, const std::string *filenames);
	Animation getAnimation(const std::string &name);

private:
	AnimationCatalog();
	~AnimationCatalog();

	AnimationCatalog(const AnimationCatalog &ctlg){ assert(false); }

	std::map<std::string, Animation*> animations;

	static AnimationCatalog *singletonInstance;
};



#endif
