#include "FishLayer.h"
#include "Fish.h"
using namespace cocos2d;

char*Fish::FISH_RESOURCES = "FishResource/Pic/0%d/%d_%d.png";

DirPath Fish::_DirPath[20] =
{
	// ÓÒÉÏ½Ç
	{ Vec2(-100, 0), Vec2(900, 600) },
	{ Vec2(-100, 0), Vec2(900, 600) },
	{ Vec2(-100, 0), Vec2(900, 600) },
	{ Vec2(-100, 0), Vec2(900, 600) },
	{ Vec2(-100, 0), Vec2(900, 600) },
	
	// ×óÉÏ½Ç
	{ Vec2(-100, 0), Vec2(900, 600) },
	{ Vec2(-100, 0), Vec2(900, 600) },
	{ Vec2(-100, 0), Vec2(900, 600) },
	{ Vec2(-100, 0), Vec2(900, 600) },
	{ Vec2(-100, 0), Vec2(900, 600) },

	// ÓÒÏÂ½Ç
	{ Vec2(-100, 0), Vec2(900, 600) },
	{ Vec2(-100, 0), Vec2(900, 600) },
	{ Vec2(-100, 0), Vec2(900, 600) },
	{ Vec2(-100, 0), Vec2(900, 600) },
	{ Vec2(-100, 0), Vec2(900, 600) },
	
	// ×óÏÂ½Ç
	{ Vec2(-100, 0), Vec2(900, 600) },
	{ Vec2(-100, 0), Vec2(900, 600) },
	{ Vec2(-100, 0), Vec2(900, 600) },
	{ Vec2(-100, 0), Vec2(900, 600) },
	{ Vec2(-100, 0), Vec2(900, 600) },
};


Fish* Fish::create(FishLayer* layer, FishInfo info)
{
	Fish* fish = new Fish();
	if (fish&&fish->init(layer, info))
	{
		fish->autorelease();
		return fish;
	}
	CC_SAFE_DELETE(fish);
	return nullptr;
}

bool Fish::init(FishLayer* layer, FishInfo info)
{
	if (!BaseObject::init())
	{
		return false;
	}

	_fishLayer = layer;
	_fishInfo = info;
	this->_initObject = std::bind(&Fish::initObject, this);
	this->_destoryObject = std::bind(&Fish::destoryObject, this);
	return true;
}

void Fish::initObject()
{
	const std::string fishName = String::createWithFormat(FISH_RESOURCES, _fishInfo.fishType, _fishInfo.fishType, 0)->_string;
	_fishSprite = cocos2d::Sprite::createWithSpriteFrameName(fishName);
	setContentSize(_fishSprite->getContentSize());
	addChild(_fishSprite);
	this->playSwingAnimation();
}

void Fish::destoryObject()
{
	this->stopAllActions();
}

void Fish::deleteMe()
{
	_fishLayer->removeFishSigine(this);
}

void Fish::playSwingAnimation()
{
	Vector<SpriteFrame*>_animFrames;
	const int frames = _fishInfo.fishSwingFrames;
	for (int i = 0; i < frames; i++)
	{
		std::string frameName = String::createWithFormat(FISH_RESOURCES, _fishInfo.fishType, _fishInfo.fishType, i)->_string;
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
		_animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(_animFrames, 0.1f);
	auto action = RepeatForever::create(Animate::create(animation));
	action->setTag(FishStatus::FISH_MOVE);
	_fishSprite->runAction(action);
}

void Fish::playDeadAnimation()
{
	this->stopAllActions();
	_fishSprite->stopActionByTag(FishStatus::FISH_MOVE);
	Vector<SpriteFrame*>_animFrames;
	const int frames = _fishInfo.fishDeadFrames;
	for (int i = 0; i < frames; i++)
	{
		std::string frameName = String::createWithFormat("FishResource/Pic/0%d/%d_d%d.png", _fishInfo.fishType, _fishInfo.fishType, i)->_string;
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
		_animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(_animFrames, 0.1f);
	animation->setLoops(3);
	auto action = Animate::create(animation);
	auto fadeOut = FadeOut::create(0.6f);
	auto callFunc = CallFunc::create(CC_CALLBACK_0(Fish::deleteMe, this));
	auto seqence = Sequence::create(action, fadeOut, callFunc, nullptr);
	seqence->setTag(FishStatus::FISH_DEAD);
	_fishSprite->runAction(seqence);
}

void Fish::move()
{
	unsigned int randomType = cocos2d::random() % 4;
	if (randomType == 0){
		moveWithDirPath();
	}
	else if (randomType == 1){
		moveWithAutoPath();
	}
	else if (randomType == 2){
		moveWithCirclePath();
	}
	else if (randomType == 3){
		moveWithBezierPath();
	}
}

void Fish::moveWithDirPath()
{
	unsigned int randomType = cocos2d::random() % 20;
	this->moveWithStraight(_DirPath[randomType].startPos, _DirPath[randomType].endedPos);
}

void Fish::moveWithAutoPath()
{
	Size fishSize = _fishSprite->getContentSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 satrtPos, endedPos;
	float radius = (fishSize.width > fishSize.height ? fishSize.width : fishSize.height) / 2;
	switch (rand() % 2) {
	case 0:{
		satrtPos.x = -radius;
		satrtPos.y = rand() % (int)visibleSize.height;
		endedPos.x = visibleSize.width + radius;
		endedPos.y = rand() % (int)visibleSize.height;
		break;
	}
	case 1:{
		satrtPos.x = visibleSize.width + radius;
		satrtPos.y = rand() % (int)visibleSize.height;
		endedPos.x = -radius;
		endedPos.y = rand() % (int)visibleSize.height;
		break;
	}
	default:
		break;
	}
	this->moveWithStraight(satrtPos, endedPos);
}

void Fish::moveWithCirclePath()
{}
void Fish::moveWithBezierPath()
{}

void Fish::moveWithStraight(cocos2d::Vec2 startPos, cocos2d::Vec2 endedPos)
{
	float distance = startPos.getDistance(endedPos);
	float duration = distance / 100.0f;
	auto move = MoveTo::create(duration, endedPos);
	CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Fish::deleteMe, this));
	Sequence* sequence = Sequence::create(move, callFunc, nullptr);
	runAction(sequence);
}

int Fish::getExpByType()
{
	return 0;
}
int Fish::getGoldByType()
{
	return 0;
}


