#ifndef __FISH__LAYER__H__H__
#define __FISH__LAYER__H__H__
#include "Fish.h"
#include "Task.h"
#include "BaseLayer.h"

class Fish;
class Bullet;
class Net;
class Lightting;
class FishLayer :public BaseLayer
{
public:
	static FishLayer* create(GameScene* scene);
	bool init(GameScene* scene);
	inline void setTask(bool a){ _isTasking = a; };
	inline bool getTask(){ return _isTasking; };
	inline void setLingtting(bool a){ _isLignting = a; };
	inline bool getLingtting(){ return _isLignting; };
private:
	cocos2d::Vector<Fish*>& getFishPool(){ return _fishPool; }
	cocos2d::Vector<Bullet*>& getBulletPool(){ return _bulletPool; }
	cocos2d::Vector<Net*>& getNetPool(){ return _netPool; }
private:
	void doEvent();
	void doUI();
	void removeEvent();
private:
	void createFish(); // 增加鱼的主入口
	// 按照特定的类型创建鱼
	void createFishByType(int type);
	void createFishByPath(int type);
	// 
	void createFishSigine(float delta);
	void createFishProps(float delta);

	// 
	void createFishFormation(float delta);
	void createFishSigineFormation(float delta);

	// task
	void createTask(float delta);

public: //  add bullet
	void createBulletAt(cocos2d::Vec2 location, int type);
	void createLightingAt(cocos2d::Vec2 location);
	void createNetAt(cocos2d::Vec2 location, int type);
public:  //  remove object
	void removeFishSigine(Fish* fish);
	void removeBulletSigine(Bullet* bullet);
	void removeNetSigine(Net* net);
	void removeFishWithBloomb();
public: // refreshUI
	void refreshUI();

private: // check collision
	void update(float delta);
	void checkOutCollision();
	bool checkOutCollisionBetweenFishesAndBullet();
	void checkOutCollisionBetweenFishesAndFishingNet();
	void fishWillBeCatched(Fish* fish, Net* net);
private: // object pool
	cocos2d::Vector<Fish*>_fishPool;
	cocos2d::Vector<Bullet*>_bulletPool;
	cocos2d::Vector<Net*>_netPool;
private:
	static FishInfo _staicFishData[12];
	static TaskData _taskData[6];
private:
	int _randFishType;
	int _randFishWayType;
	bool _isTasking;
	bool _isLignting;

	TaskData _data;
	Lightting*_light;
};

#endif
