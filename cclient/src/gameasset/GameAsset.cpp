#include "GameAsset.h"

#include <cstdlib>

shared_ptr<NullGameAsset> NullGameAsset::instance;

NullGameAsset::NullGameAsset(){}

shared_ptr<NullGameAsset> NullGameAsset::getInstance(){
	if(instance == NULL){
		instance = shared_ptr<NullGameAsset>(new NullGameAsset());
	}
	return instance;
}

GameAssetType NullGameAsset::getType() const { return GAME_ASSET_NONE; }