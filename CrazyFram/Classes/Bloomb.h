#ifndef __BLOOMB__H__H__
#define __BLOOMB__H__H__
#include "BaseObject.h"
class FishLayer;
class Bloomb :public BaseObject
{
public:
	static Bloomb* create(FishLayer* layer, cocos2d::Vec2 location);
private:
	bool init(FishLayer* layer, cocos2d::Vec2 location);
	void initObject();
	void destoryObject();
	void deleteMe();
private:
	FishLayer* _fishLayer;
	cocos2d::Vec2 _location;
	cocos2d::Sprite* _boombSprite;


};
#endif