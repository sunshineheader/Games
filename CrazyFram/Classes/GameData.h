#ifndef __GAME__HELPER__H__H__
#define __GAME__HELPER__H__H__
#include "cocos2d.h"

class GameData {

public:
	GameData();
	~GameData();
	static GameData* getInstance();
	static void destoryInstance();
public:
private:
	static GameData* _instance;


};

#endif // !__GAME__HELPER__H__H__