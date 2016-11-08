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
public:
	void savePlayerGold();
private:
	static GameData* _instance;
	int _golds;


};

#endif // !__GAME__HELPER__H__H__