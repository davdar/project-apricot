#include "GameData.h"

#include <cstdlib>

GameData::GameData(GameDataType instanceType):instanceType(instanceType){}

shared_ptr<NullGameData> NullGameData::instance;

NullGameData::NullGameData():GameData(NullGameData::type){}

shared_ptr<NullGameData> NullGameData::getInstance(){
	if(instance == NULL){
		instance = shared_ptr<NullGameData>(new NullGameData());
	}
	return instance;
}

GameDataType NullGameData::getType() const { return GAME_DATA_NULL; } 