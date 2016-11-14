
#ifndef __FISH__NET__H__H
#define __FISH__NET__H__H
#include "BaseObject.h"

enum  NetType
{
	NET_TYPE_00,
	NET_TYPE_01,
	NET_TYPE_02,
	NET_TYPE_03,
	NET_TYPE_04,
	NET_TYPE_05,
	NET_TYPE_06
};

class FishLayer;
class Net : public BaseObject {

public:
	static Net* create(FishLayer* layer, NetType type);
private:
	bool init(FishLayer* layer, NetType type);
	void initObject();
	void destoryObject();
	cocos2d::Action* netAction();
	void deleteMe();
public:
	cocos2d::Rect getCollisionRect();
	int getType();
private:
	FishLayer* _fishLayer;
	cocos2d::Sprite* _netSprite;
	NetType _type;

};

#endif