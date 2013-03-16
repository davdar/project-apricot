#ifndef _GAME_DATA_H
#define _GAME_DATA_H

#include "../types.h"
#include "GameDataTypes.h"

class GameData {
public:
	GameData(GameDataType instanceType);
	GameDataType getType() const { return instanceType; }

private:
	GameDataType instanceType;
};

class NullGameData : public GameData {
public:
	static const GameDataType type = GAME_DATA_NULL;

	static shared_ptr<NullGameData> getInstance();

	virtual GameDataType getType() const;

private:
	static shared_ptr<NullGameData> instance;

	NullGameData();
};

#endif