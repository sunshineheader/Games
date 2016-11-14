#include "FishLayer.h"
#include "Bloomb.h"

using namespace cocos2d;

Bloomb* Bloomb::create(FishLayer* layer, cocos2d::Vec2 location)
{
	Bloomb* fish = new Bloomb();
	if (fish&&fish->init(layer, location))
	{
		fish->autorelease();
		return fish;
	}
	CC_SAFE_DELETE(fish);
	return nullptr;
}

bool Bloomb::init(FishLayer* layer, cocos2d::Vec2 location)
{
	if (!BaseObject::init())
	{
		return false;
	}

	_fishLayer = layer;
	_location = location;
	this->_initObject = std::bind(&Bloomb::initObject, this);
	this->_destoryObject = std::bind(&Bloomb::destoryObject, this);
	return true;
}

void Bloomb::initObject()
{
	setPosition(_location);
	const std::string netName = String::createWithFormat("Prop/firez100.png")->_string;
	_boombSprite = cocos2d::Sprite::createWithSpriteFrameName(netName);
	addChild(_boombSprite);
	
	Vector<SpriteFrame*>_animFrames;
	const int frames = 9;
	for (int i = 0; i < frames; i++)
	{
		std::string frameName = String::createWithFormat("Prop/firez10%d.png", i)->_string;
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
		_animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(_animFrames, 0.1f);
	auto action = Animate::create(animation);

	CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Bloomb::deleteMe, this));
	Sequence* seqence = Sequence::create(action, callFunc, nullptr);
	_boombSprite->runAction(seqence);
}

void Bloomb::deleteMe()
{
	this->removeFromParentAndCleanup(true);
}

void Bloomb::destoryObject()
{
	this->stopAllActions();
}



