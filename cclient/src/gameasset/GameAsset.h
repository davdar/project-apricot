#ifndef _GAME_ASSET_H
#define _GAME_ASSET_H

#include "GameAssetTypes.h"

class GameAsset {
public:
	virtual GameAssetType getType() const = 0;
};

class NullGameAsset : public GameAsset {
public:
	static NullGameAsset *getInstance();

	virtual GameAssetType getType() const;

private:
	static NullGameAsset *instance;

	NullGameAsset();
};

#endif