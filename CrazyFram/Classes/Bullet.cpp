#include "FishLayer.h"
#include "Bullet.h"


Bullet* Bullet::create(FishLayer* layer, BulletType type)
{
	Bullet* fish = new Bullet();
	if (fish&&fish->init(layer, type))
	{
		fish->autorelease();
		return fish;
	}
	CC_SAFE_DELETE(fish);
	return nullptr;
}

bool Bullet::init(FishLayer* layer, BulletType type)
{
	if (!BaseObject::init())
	{
		return false;
	}
	_fishLayer = layer;
	_type = type;
	this->_initObject = std::bind(&Bullet::initObject, this);
	this->_destoryObject = std::bind(&Bullet::destoryObject, this);
	return true;
}

void Bullet::initObject()
{
	if (_type == BulletType::BULLET_TYPE_07) {

	}
	else {
		const std::string bulletName = String::createWithFormat("bullet0%d.png", _type + 1)->_string;
		_bulletSprite = cocos2d::Sprite::createWithSpriteFrameName(bulletName);
		addChild(_bulletSprite);
	}
}

void Bullet::destoryObject()
{
	this->stopAllActions();
}

void Bullet::flyTo(cocos2d::Vec2 targetInWorldSpace)
{
	cocos2d::Vec2 targetInNodeSpace = this->getParent()->convertToNodeSpace(targetInWorldSpace);
	float angle = GameHelper::getAngle(this->getPosition(), targetInWorldSpace);
	this->setRotation(angle);
	float speed = 300.0f;
	float duration = (this->getPosition().getDistance(targetInWorldSpace)) / speed;
	cocos2d::CallFunc* callFunc = cocos2d::CallFunc::create(CC_CALLBACK_0(Bullet::deleteMe, this));
	cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(duration, targetInNodeSpace);
	cocos2d::Sequence* sequence = cocos2d::Sequence::create(moveTo, callFunc, nullptr);
	this->runAction(sequence);
}

cocos2d::Vec2 Bullet::getCollisionPoint()
{
	return this->getParent()->convertToWorldSpace(this->getPosition());
}

void Bullet::deleteMe()
{
	_fishLayer->removeBulletSigine(this);
}