#ifndef __GOLD__H__H__
#define __GOLD__H__H__

#include "BaseObject.h"

class MenuLayer;
class Gold :public BaseObject
{
public:
	static Gold* create(MenuLayer* layer, cocos2d::Vec2 satrtPos, cocos2d::Vec2 endedPos);
private:
	bool init(MenuLayer* layer, cocos2d::Vec2 satrtPos, cocos2d::Vec2 endedPos);
	void initObject();
	void destoryObject();
	cocos2d::Action* goldAnimation();
	cocos2d::Action* goldAction();
	void deleteMe();
private:
	MenuLayer* _fishLayer;
	cocos2d::Sprite*_goldSprite;
	cocos2d::Vec2 _satrtPos;
	cocos2d::Vec2 _endedPos;
};

#endif


