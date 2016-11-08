#ifndef __FISH__LAYER__H__H__
#define __FISH__LAYER__H__H__
#include "Fish.h"
#include "BaseLayer.h"

class Fish;
class Bullet;
class Net;

class FishLayer :public BaseLayer
{
public:
	static FishLayer* create(GameScene* scene);
	bool init(GameScene* scene);
private:
	cocos2d::Vector<Fish*>& getFishPool(){ return _fishPool; }
	cocos2d::Vector<Bullet*>& getBulletPool(){ return _bulletPool; }
	cocos2d::Vector<Net*>& getNetPool(){ return _netPool; }

private:
	void doEvent();
	void doUI();
	void removeEvent();
private: //  add fish
	void createFish();
	void createFishWithType(int type);
	void createFishWithSigine(float delta);
	void createFishWithMore(float delta);
	void createFishWithFormation(float delta);	// ����
private: // add porpos
	void createFishWithProps(float delta);
public: //  add bullet
	void createBulletAt(cocos2d::Vec2 location, int type);
	void createLightingAt(cocos2d::Vec2 location);
	void createNetAt(cocos2d::Vec2 location, int type);
public:  //  remove object
	void removeFishSigine(Fish* fish);
	void removeBulletSigine(Bullet* bullet);
	void removeNetSigine(Net* net);

public: // refreshUI
	void refreshUI();

private: // check collision
	void update(float delta);
	void checkOutCollision();
	bool checkOutCollisionBetweenFishesAndBullet();
	void checkOutCollisionBetweenFishesAndFishingNet();

private: // object pool
	cocos2d::Vector<Fish*>_fishPool;
	cocos2d::Vector<Bullet*>_bulletPool;
	cocos2d::Vector<Net*>_netPool;
private:
	static FishInfo _staicFishData[12];





	///////// MYTest ///////
private:




};

#endif
