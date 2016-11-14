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
	if (!BaseObject::init()) {
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
	}
	else{
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
	float distanceY = location.y - this->getPosition().y;
	float distanceX = location.x - this->getPosition().x;
	float radian = Vec2(distanceY, distanceX).getAngle();
	float angle = CC_RADIANS_TO_DEGREES(radian);
	this->setRotation(angle);
	this->playCannonAnimation();
}
void Cannon::playCannonAnimation()
{
	Vector<SpriteFrame*>_animFrames;
	int frames = 2;
	if (_type == CannonType::CANNON_TYPE_07) {
		
		for (int i = 0; i < frames; i++) {
			const std::string frameName = String::createWithFormat("actor_cannon_jiguang_0%d.png", i + 1)->_string;
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
			_animFrames.pushBack(frame);
		}
	}
	else {
		for (int i = 0; i < frames; i++) {
			const std::string frameName = String::createWithFormat("actor_cannon1_%d%d.png", _type + 1, i + 1)->_string;
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
			_animFrames.pushBack(frame);
		}
	}

	auto animation = Animation::createWithSpriteFrames(_animFrames, 0.1);
	animation->setRestoreOriginalFrame(true);
	auto action = Animate::create(animation);
	_cannonSprite->runAction(action);
}