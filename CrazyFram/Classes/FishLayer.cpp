#include "GameScene.h"
#include "InitObjectHeader.h"
#include "InitLayerHeader.h"


FishInfo FishLayer::_staicFishData[12] =
{
	//  类型      金币 速度 几率 经验 游动动画帧数
	{ FishType(0), 1,  200, 1.0f, 1,  1,8, 2 },
	{ FishType(1), 2,  200, 1.0f, 2,  1,12, 2 },
	{ FishType(2), 4,  150, 1.0f, 5,  1,13, 3 },
	{ FishType(3), 8,  150, 1.0f, 5,  1,10, 3 },
	{ FishType(4), 10, 150, 1.0f, 10, 1, 12, 2 },
	{ FishType(5), 20, 100, 1.0f, 10, 1,8, 6 },
	{ FishType(6), 50, 80,  0.6f, 20, 1, 12, 3 },
	{ FishType(7), 80, 80,  0.6f, 30, 1,10, 3 },
	{ FishType(8), 100,60,  0.4f, 50, 1, 12, 3 },
	{ FishType(9), 200,60,  0.3f, 100,1, 12, 3 },
	{ FishType(10),200, 60, 1.0f, 100,0, 0, 0 },
	{ FishType(11),200, 60, 1.0f, 100,0, 0, 0 },
};


FishLayer* FishLayer::create(GameScene* scene)
{
	FishLayer* layer = new FishLayer();
	if (layer && layer->init(scene))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool FishLayer::init(GameScene* scene)
{
	BaseLayer::init(scene);
	// init pools
	_fishPool.reserve(4);
	_bulletPool.reserve(4);
	_netPool.reserve(4);
	// override 
	this->_doEvent = std::bind(&FishLayer::doEvent, this);
	this->_doUI = std::bind(&FishLayer::doUI, this);
	this->_removeEvent = std::bind(&FishLayer::removeEvent, this);
	return true;
}

void FishLayer::doEvent()
{
	scheduleUpdate();
}
void FishLayer::doUI()
{
	createFish();
}
void FishLayer::removeEvent()
{
	unscheduleUpdate();
}
void FishLayer::createFish()
{
	// 每秒随机游动
	schedule(schedule_selector(FishLayer::createFishSigine),    1.0f, CC_REPEAT_FOREVER, 0.0f);
	schedule(schedule_selector(FishLayer::createFishFormation), 20.0f, CC_REPEAT_FOREVER, 0.0f);
	schedule(schedule_selector(FishLayer::createFishProps), 30.0f, CC_REPEAT_FOREVER, 0.0f);

}

void FishLayer::createFishByType(int type)
{
	int randrate = cocos2d::rand_0_1() ;
	if (randrate <= _staicFishData[type].fishRate)
	{
		FishInfo info = _staicFishData[type];
		Fish *fish = Fish::create(this, info);
		_fishPool.pushBack(fish);
		addChild(fish);
		fish->move(); // 随机游动
	}
}
void FishLayer::createFishByPath(int type)
{

}

void FishLayer::createFishSigine(float delta)
{
	int randtype = cocos2d::random() % 10; // 正常的鱼
	this->createFishByType(randtype);
}

void FishLayer::createFishProps(float delta)
{
	bool isRedPaper = cocos2d::random() % 2 == 1;
	if (isRedPaper) {
		this->createFishByType(10);
	}
	else {
		this->createFishByType(11);
	}
}


void FishLayer::createFishFormation(float delta)
{
	int randnumber = cocos2d::random() % 10 + 2; // 正常的鱼
	float randtime = cocos2d::rand_0_1() + 1.0f; 
	_randFishType = cocos2d::random() % 5;
	_randFishWayType = cocos2d::random() % 12;
	schedule(schedule_selector(FishLayer::createFishSigineFormation), randtime, randnumber, 0.0f);
}

void  FishLayer::createFishSigineFormation(float delta)
{
	int randrate = cocos2d::rand_0_1();
	if (randrate <= _staicFishData[_randFishType].fishRate)
	{
		FishInfo info = _staicFishData[_randFishType];
		Fish *fish = Fish::create(this, info);
		_fishPool.pushBack(fish);
		addChild(fish);
		fish->moveWithBezierPathByPathType(_randFishWayType); // 随机游动
	}
}

void FishLayer::createBulletAt(cocos2d::Vec2 location, int type)
{
	Bullet* bullet = Bullet::create(this,BulletType(type));
	bullet->setPosition(Vec2(400, 20));
	addChild(bullet,100);
	_bulletPool.pushBack(bullet);

	float distance = 550;
	Vec2 normal = location - bullet->getPosition();
	Vec2 normalPosition = normal.getNormalized();
	Vec2 vector = normalPosition * distance;
	Vec2 target = bullet->getPosition() + vector;
	bullet->flyTo(target);

}
void FishLayer::createLightingAt(cocos2d::Vec2 location)
{
	Lightting*light = Lightting::create(this, location);
	addChild(light);
}

void FishLayer::createNetAt(cocos2d::Vec2 location, int type)
{
	Net* net = Net::create(this, NetType(type));
	net->setPosition(location);
	_netPool.pushBack(net);
	addChild(net);
}

void FishLayer::removeFishSigine(Fish* fish)
{
	_fishPool.eraseObject(fish);
	fish->removeFromParentAndCleanup(true);
}

void FishLayer::removeBulletSigine(Bullet* bullet)
{
	_bulletPool.eraseObject(bullet);
	bullet->removeFromParentAndCleanup(true);
}

void FishLayer::removeNetSigine(Net* net)
{
	_netPool.eraseObject(net);
	net->removeFromParentAndCleanup(true);
}

void FishLayer::refreshUI()
{
	_GameScene->getMenuLayer()->refreshUI();
}

void FishLayer::update(float delta)
{
	checkOutCollision();
}

void FishLayer::checkOutCollision()
{
	bool falg = this->checkOutCollisionBetweenFishesAndBullet();
	if (falg) {
		this->checkOutCollisionBetweenFishesAndFishingNet();
	}
}
bool FishLayer::checkOutCollisionBetweenFishesAndBullet()
{
	if (!_bulletPool.empty()) {
		for (auto iter = _bulletPool.begin(); iter != _bulletPool.end(); iter++) {
			Bullet* bullet = (Bullet*)(*iter);
			for (auto iterFish = _fishPool.begin(); iterFish != _fishPool.end(); iterFish++) {
				Fish* fish = (Fish*)(*iterFish);
				if (!fish->isCatched() && fish->getCollisionRect().containsPoint(bullet->getCollisionPoint())) {
					this->createNetAt(bullet->getCollisionPoint(),bullet->getType());
					this->removeBulletSigine(bullet);
					return true;
				}
			}
		}
	}
	return false;
}
void FishLayer::checkOutCollisionBetweenFishesAndFishingNet()
{
	if (!_netPool.empty()) {
		for (auto iter = _netPool.begin(); iter != _netPool.end(); iter++) {
			Net* net = (Net*)(*iter);
			for (auto iterFish = _fishPool.begin(); iterFish != _fishPool.end(); iterFish++) {
				Fish* fish = (Fish*)(*iterFish);
				if (!fish->isCatched() && fish->getCollisionRect().intersectsRect(net->getCollisionRect())){
					fish->playDeadAnimation();
					_GameScene->getMenuLayer()->createGoldAt(false, fish->getPosition());
				}
			}
		}
	}
}