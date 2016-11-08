#include "GameScene.h"
#include "InitObjectHeader.h"
#include "InitLayerHeader.h"


FishInfo FishLayer::_staicFishData[12] =
{
	//  类型      金币 速度 几率 经验 游动动画帧数
	{ FishType(0), 1,  200, 1.0f, 1, 8, 2 },
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
	scheduleUpdate();

	return true;
}

void FishLayer::doEvent()
{
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
	schedule(schedule_selector(FishLayer::createFishWithSigine), 1.0f, CC_REPEAT_FOREVER, 0.0f);
	//schedule(schedule_selector(FishLayer::createFishWithProps), 30.0f, CC_REPEAT_FOREVER, 0.0f);
	schedule(schedule_selector(FishLayer::createFishWithMore), 5.0f, CC_REPEAT_FOREVER, 0.0f);

}

void FishLayer::createFishWithType(int type)
{
	if (cocos2d::rand_0_1() <= _staicFishData[type].fishRate)
	{
		Fish* fish = Fish::create(this, _staicFishData[type]);
		_fishPool.pushBack(fish);
		addChild(fish);
		fish->move();
	}
}

void FishLayer::createFishWithSigine(float delta)
{
	int type = cocos2d::random() % 10;
	this->createFishWithType(type);
}

void FishLayer::createFishWithMore(float delta)
{
	int number = cocos2d::random() % 10;
	while (number >= 0)
	{
		number -- ;
		int type = cocos2d::random() % 10;
		this->createFishWithType(type);
	}
}

void FishLayer::createFishWithFormation(float delta)// 阵型
{
	// TOOD 创建阵型
	// 1.直线阵型
	// 1.1 一种鱼的直线阵型
	// 1.2 多种鱼的直线阵型

	// 2.曲线阵型
	// 2.1 一种鱼的曲线阵型
	// 2.2 多种鱼的曲线阵型
}

void FishLayer::createFishWithProps(float delta)
{
	int randomType = cocos2d::random() % 2;
	if (randomType == 0) {
		this->createFishWithType(10);
	}
	else{
		this->createFishWithType(11);
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
{}

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
	if (falg)
	{
		this->checkOutCollisionBetweenFishesAndFishingNet();
	}
}
bool FishLayer::checkOutCollisionBetweenFishesAndBullet()
{
	if (!_bulletPool.empty())
	{
		for (auto iter = _bulletPool.begin(); iter != _bulletPool.end(); iter++)
		{
			Bullet* bullet = (Bullet*)(*iter);
			for (auto iterFish = _fishPool.begin(); iterFish != _fishPool.end(); iterFish++)
			{
				Fish* fish = (Fish*)(*iterFish);
				Rect rect = fish->getCollisionRect();
				if (fish->getCollisionRect().containsPoint(bullet->getCollisionPoint()))
				{
					// checkOutCollisionBetweenFishesAndBullet() angin 
					this->createNetAt(bullet->getPosition(),bullet->getType());
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
	if (!_netPool.empty())
	{
		for (auto iter = _netPool.begin(); iter != _netPool.end(); iter++)
		{
			Net* net = (Net*)(*iter);
			for (auto iterFish = _fishPool.begin(); iterFish != _fishPool.end(); iterFish++)
			{
				// TOOD 
				if (true)
				{
				}
			}
		}
	}
}