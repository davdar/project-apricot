#ifndef _HERO_H
#define _HERO_H

#include "GameData.h"

class Hero : public GameData {
public:
	GameDataType getType() const;
};

#endif