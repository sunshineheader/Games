#ifndef _GAME__DATA__H__H__
#define _GAME__DATA__H__H__
#include "cocos2d.h"

class GameData {

public:
	GameData();
	~GameData();
	static GameData* getInstance();
	static void destoryInstance();
public:
	int getPlayerGold();
	inline void setPlayerGold(int gold){ _golds = gold; };

	int getPlayerCurrcertLevel();
	inline void setPlayerCurrcertLevel(int level){ _level = level; };

	int getPlayerLevelExp();
	inline void setPlayerLevelExp(int exp){ _levelExp = exp; };

	int getLightLevelExp();
	inline void setLightLevelExp(int exp){ _lightExp = exp; };

	int getCannonType();
	inline void setCannonType(int type){ _lightExp = type; };
public:
	void savePlayerGold();
	void savePlayerLevelExp();
	void saveLightLevelExp();
	void savePlayerCurrcertLevel();
	void saveCannonType();

private:
	static GameData* _instance;
	int _golds;
	int _level;
	int _levelExp;
	int _lightExp;
	int _cannonType;




};

#endif // !__GAME__HELPER__H__H__