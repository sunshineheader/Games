#ifndef __LIGHTTING__OBJECT__H__H__
#define __LIGHTTING__OBJECT__H__H__
#include "BaseObject.h"

class FishLayer;
class Lightting :public BaseObject
{
public:
	static Lightting* create(FishLayer* layer,cocos2d::Vec2 location);
private:
	bool init(FishLayer* layer, cocos2d::Vec2 location);
	void initObject();
	void destoryObject();
	cocos2d::Rect getCollisionRect();
	cocos2d::Action* lightingAnimation();
	cocos2d::Action* lightingAction();
private:
	FishLayer*_fishLayer;
	cocos2d::Sprite* _lightSprite;
	cocos2d::Vec2 _location;
};
#endif




