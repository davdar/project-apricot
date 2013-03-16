#ifndef _GAME_DATA_TYPES_H
#define _GAME_DATA_TYPES_H

#define LIST_GAME_DATA_TYPES(OP) \
	OP(GAME_DATA_NULL) \
	OP(GAME_DATA_MAP) \
	OP(GAME_DATA_HERO)


#define MAKE_SYM(VAR) VAR,
enum GameDataType {
	LIST_GAME_DATA_TYPES(MAKE_SYM)
};

#define MAKE_STR(VAR) #VAR,
static const char * const gameDataTypeStrings[] = {
	LIST_GAME_DATA_TYPES(MAKE_STR)
};

inline const char *str(GameDataType type){ return gameDataTypeStrings[type]; }

/*
 * Gotta be a better way of doing this???
 * Maybe strings? (How to easily enforce uniqueness?)
 */
/*
enum GameDataType {
	GAME_DATA_NULL,
	GAME_DATA_MAP,
	GAME_DATA_HERO
};
*/

#undef LIST_GAME_DATA_TYPES
#undef MAKE_SYM
#undef MAKE_STR

#endif