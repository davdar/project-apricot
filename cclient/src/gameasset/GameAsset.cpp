#include "GameAsset.h"

#include <cstdlib>

NullGameAsset *NullGameAsset::instance = NULL;

NullGameAsset::NullGameAsset(){}

NullGameAsset *NullGameAsset::getInstance(){
	if(instance == NULL){
		instance = new NullGameAsset();
	}
	return instance;
}

GameAssetType NullGameAsset::getType() const { return GAME_ASSET_NONE; }