#ifndef __CANNON__OBJECT__H__H__
#define __CANNON__OBJECT__H__H__
#include "BaseObject.h"

enum CannonType
{
	CANNON_TYPE_00,
	CANNON_TYPE_01,
	CANNON_TYPE_02,
	CANNON_TYPE_03,
	CANNON_TYPE_04,
	CANNON_TYPE_05,
	CANNON_TYPE_06,
	CANNON_TYPE_07 // Lightting 
};
typedef struct
{
	CannonType cannonType;
	float cannonPrice;
}CannonData;


class MenuLayer;
class Cannon :public BaseObject
{
public:
	static Cannon* create(MenuLayer* layer, CannonType type = CannonType::CANNON_TYPE_00);
private:
	bool init(MenuLayer* layer, CannonType type);
	void initObject();
	void destoryObject();
private: // cannon sprite
	void cahngeCannonSpriteByType();
public:
	void setType(CannonType type);
	CannonType getType();
	void cannonAimat(cocos2d::Vec2 location);

private:
	MenuLayer* _menuLayer;
	cocos2d::Sprite* _cannonSprite;
	CannonType _type;
};


#endif