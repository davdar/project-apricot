#ifndef _HERO_H
#define _HERO_H

#include "GameData.h"

class Hero : public GameData {
public:
	static const GameDataType type = GAME_DATA_HERO;

public:
	Hero();
};

#endif