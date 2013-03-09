#ifndef _HERO_H
#define _HERO_H

#include "GameAsset.h"

class Hero : public GameAsset {
public:
	GameAssetType getType() const;
};

#endif