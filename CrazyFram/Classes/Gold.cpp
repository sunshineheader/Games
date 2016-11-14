#include "FishLayer.h"
#include "Gold.h"
using namespace cocos2d;

Gold* Gold::create(MenuLayer* layer, cocos2d::Vec2 satrtPos, cocos2d::Vec2 endedPos)
{
	Gold* fish = new Gold();
	if (fish&&fish->init(layer, satrtPos, endedPos))
	{
		fish->autorelease();
		return fish;
	}
	CC_SAFE_DELETE(fish);
	return nullptr;
}

bool Gold::init(MenuLayer* layer, cocos2d::Vec2 satrtPos, cocos2d::Vec2 endedPos)
{
	if (!BaseObject::init())
	{
		return false;
	}
	_fishLayer = layer;
	_satrtPos = satrtPos;
	_endedPos = endedPos;
	this->_initObject = std::bind(&Gold::initObject, this);
	this->_destoryObject = std::bind(&Gold::destoryObject, this);
	return true;
}

void Gold::initObject()
{
	_goldSprite = Sprite::createWithSpriteFrameName("jinbi_1.png");
	addChild(_goldSprite);
	_goldSprite->runAction(this->goldAnimation());
	setPosition(_satrtPos);
	this->setScale(0.6);
	this->runAction(this->goldAction());
}

void Gold::destoryObject()
{
	this->stopAllActions();
}

Action* Gold::goldAnimation()
{
	Vector<SpriteFrame*>_animFrames;
	const int frames = 5;
	for (int i = 0; i < frames; i++)
	{
		std::string frameName = String::createWithFormat("jinbi_%d.png", i + 1)->_string;
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
		_animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(_animFrames, 0.1f);
	return RepeatForever::create(Animate::create(animation));
}

Action* Gold::goldAction()
{
	float distance = _satrtPos.getDistance(_endedPos);
	float duration = distance / 400.0f;
	auto move = MoveTo::create(duration, _endedPos);
	auto fadeOut = FadeOut::create(0.2);
	auto callFunc = CallFunc::create(CC_CALLBACK_0(Gold::deleteMe, this));
	return Sequence::create(move, fadeOut, callFunc, nullptr);
}

void Gold::deleteMe()
{
	this->removeFromParentAndCleanup(true);
}

