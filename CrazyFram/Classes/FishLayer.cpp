#include "GameScene.h"
#include "InitObjectHeader.h"
#include "InitLayerHeader.h"


FishInfo FishLayer::_staicFishData[12] =
{
	//  类型      金币 速度 几率 经验 游动动画帧数
	{ FishType(0), 1,  400, 1.0f, 1, 8, 2 },
	{ FishType(1), 2,  200, 1.0f, 2, 12, 2 },
	{ FishType(2), 4,  150, 1.0f, 5, 13, 3 },
	{ FishType(3), 8,  150, 1.0f, 5, 10, 3 },
	{ FishType(4), 10, 150, 1.0f, 10, 12, 2 },
	{ FishType(5), 20, 100, 1.0f, 10, 8, 6 },
	{ FishType(6), 50, 80, 0.6f, 20, 12, 3 },
	{ FishType(7), 80, 80, 0.6f, 30, 10, 3 },
	{ FishType(8), 100,60, 0.4f, 50, 12, 3 },
	{ FishType(9), 200,60, 0.3f, 100, 12, 3 },
	{ FishType(10),200, 60, 1.0f, 100, 0, 0 },
	{ FishType(11),200, 60, 1.0f, 100, 0, 0 },
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
{}

void FishLayer::doUI()
{
	createFish();
}

void FishLayer::removeEvent()
{}

void FishLayer::createFish()
{
	createFishWithSigine();
}

void FishLayer::createFishWithSigine()
{
	// TOOD :出现概率
	int randomType = cocos2d::random() % 10;
	Fish* fish = Fish::create(this, _staicFishData[9]);
	fish->setPosition(Vec2(400,240));
	addChild(fish);
}

void FishLayer::createFishWithMore()
{}

void FishLayer::createFishWithType()
{}

void FishLayer::createFishWithProps()
{}

void FishLayer::createBulletAt(cocos2d::Vec2 location, int type)
{
	Bullet* bullet = Bullet::create(this,BulletType(type));
	bullet->setPosition(Vec2(400, 20));
	addChild(bullet,100);
	_bulletPool.pushBack(bullet);
	// 
	float distance = 550;
	Vec2 normal = location - bullet->getPosition();
	Vec2 normalPosition = normal.getNormalized();
	Vec2 vector = normalPosition * distance;
	Vec2 target = bullet->getPosition() + vector;
	bullet->flyTo(target);

}
void FishLayer::createLightingAt(cocos2d::Vec2 location)
{}

void FishLayer::createNetAt(cocos2d::Vec2 location)
{}

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

void FishLayer::checkOutCollision()
{
	bool falg = this->checkOutCollisionBetweenFishesAndBullet();
	if (falg)
	{
		this->checkOutCollisionBetweenFishesAndFishingNet();
	}
}
bool FishLayer::checkOutCollisionBetweenFishesAndBullet()
{
	return true;
}
void FishLayer::checkOutCollisionBetweenFishesAndFishingNet()
{}