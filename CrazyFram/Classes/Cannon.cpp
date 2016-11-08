#include "MenuLayer.h"
#include "Cannon.h"
Cannon* Cannon::create(MenuLayer* layer, CannonType type)
{
	Cannon* fish = new Cannon();
	if (fish&&fish->init(layer, type))
	{
		fish->autorelease();
		return fish;
	}
	CC_SAFE_DELETE(fish);
	return nullptr;
}

bool Cannon::init(MenuLayer* layer, CannonType type )
{
	if (!BaseObject::init())
	{
		return false;
	}

	_menuLayer = layer;
	_type = type;
	this->_initObject = std::bind(&Cannon::initObject, this);
	this->_destoryObject = std::bind(&Cannon::destoryObject, this);
	return true;
}

void Cannon::initObject()
{
	if (_type == CannonType::CANNON_TYPE_07) {
		const std::string cannonName = "actor_cannon_jiguang_01.png";
		_cannonSprite = cocos2d::Sprite::createWithSpriteFrameName(cannonName);
		_cannonSprite->setAnchorPoint(Vec2(0.5, 0.2));
		addChild(_cannonSprite);
		setContentSize(_cannonSprite->getContentSize());
	}
	else {
		const std::string cannonName = String::createWithFormat("actor_cannon1_%d1.png",_type + 1)->_string;
		_cannonSprite = cocos2d::Sprite::createWithSpriteFrameName(cannonName);
		_cannonSprite->setAnchorPoint(Vec2(0.5, 0.2));
		addChild(_cannonSprite);
		setContentSize(_cannonSprite->getContentSize());
	}
}

void Cannon::destoryObject()
{}

void Cannon::cahngeCannonSpriteByType()
{

	if (_type == CannonType::CANNON_TYPE_07) {
		const std::string cannonName = "actor_cannon_jiguang_01.png";
		_cannonSprite->setSpriteFrame(cannonName);
	}else{
		const std::string cannonName = String::createWithFormat("actor_cannon1_%d1.png", _type + 1)->_string;
		_cannonSprite->setSpriteFrame(cannonName);
	}

	_menuLayer->setTouchedEnable(true);
}

void Cannon::setType(CannonType type)
{
	_type = type;
	_menuLayer->setTouchedEnable(false);
	cahngeCannonSpriteByType();
}

CannonType Cannon::getType()
{
	return _type ;
}

void Cannon::cannonAimat(cocos2d::Vec2 location)
{
	float angle = GameHelper::getAngle(this->getPosition(), location);
	this->setRotation(angle);
}
