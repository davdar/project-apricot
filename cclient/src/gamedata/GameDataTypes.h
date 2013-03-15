#ifndef _GAME_DATA_TYPES_H
#define _GAME_DATA_TYPES_H

/*
 * Gotta be a better way of doing this???
 * Maybe strings? (How to easily enforce uniqueness?)
 */
enum GameDataType {
	GAME_DATA_NONE,
	GAME_DATA_MAP,
	GAME_DATA_HERO
};

template <typename T>
struct GameDataTraits {};


#endif