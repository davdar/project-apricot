#ifndef _GAME_ASSET_H
#define _GAME_ASSET_H

#include "../types.h"
#include "GameAssetTypes.h"

class GameAsset {
public:
	virtual GameAssetType getType() const = 0;
};

class NullGameAsset : public GameAsset {
public:
	static shared_ptr<NullGameAsset> getInstance();

	virtual GameAssetType getType() const;

private:
	static shared_ptr<NullGameAsset> instance;

	NullGameAsset();
};

#endif