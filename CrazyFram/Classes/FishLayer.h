#ifndef __FISH__LAYER__H__H__
#define __FISH__LAYER__H__H__
#include "BaseLayer.h"

class Fish;
class FishLayer :public BaseLayer
{
public:
	static FishLayer* create(GameScene* scene);
	bool init(GameScene* scene);
public:
	cocos2d::Vector<Fish*>& getFishPool(){ return _fishPool; }
private:
	void doEvent();
	void doUI();
	void removeEvent();
private: //  add fish
	void createFish();
	void createFishWithSigine();
	void createFishWithMore();
	void createFishWithType();
public:  //   remove fish
	void removeFishSigine(Fish* fish);

private: // check collision
	void checkOutCollision();
	bool checkOutCollisionBetweenFishesAndBullet();
	void checkOutCollisionBetweenFishesAndFishingNet();

private: // object pool
	cocos2d::Vector<Fish*>_fishPool;
};

#endif
