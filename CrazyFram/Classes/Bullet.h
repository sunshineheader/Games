#ifndef __BULLET__OBJECT__H__H__
#define __BULLET__OBJECT__H__H__
#include "BaseObject.h"
enum BulletType
{
	BULLET_TYPE_00,
	BULLET_TYPE_01,
	BULLET_TYPE_02,
	BULLET_TYPE_03,
	BULLET_TYPE_04,
	BULLET_TYPE_05,
	BULLET_TYPE_06,
	BULLET_TYPE_07 // Lightting 
};
class FishLayer;
class Bullet :public BaseObject
{
public:
	static Bullet* create(FishLayer* layer, BulletType type = BulletType::BULLET_TYPE_00);
private:
	bool init(FishLayer* layer, BulletType type);
	void initObject();
	void destoryObject();
	void deleteMe();
public:
	void flyTo(cocos2d::Vec2 endedPos);
	cocos2d::Vec2 getCollisionPoint();
	BulletType getType(){ return _type; };

private:
	FishLayer* _fishLayer;
	cocos2d::Sprite* _bulletSprite;
	BulletType _type;
};
#endif