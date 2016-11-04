#ifndef __GAME_SCENE__H__H__
#define __GAME_SCENE__H__H__
#include "cocos2d.h"

class MenuLayer;
class FishLayer;

class GameScene :public cocos2d::Scene
{
public:
	CREATE_FUNC(GameScene);
	bool init();
public:
	FishLayer* getFishLayer();
	MenuLayer* getMenuLayer();

private:
	MenuLayer* _menuLayer;
	FishLayer* _fishLayer;

};


#endif // __GAME_SCENE__H__H__


