#include "FishLayer.h"
#include "CircleBy.h"
#include "CurveBy.h"
#include "Fish.h"
using namespace cocos2d;

char*Fish::FISH_RESOURCES = "FishResource/Pic/0%d/%d_%d.png";

DirPath Fish::_DirPath[20] =
{
	// ÓÒÉÏ½Ç
	{ Vec2(+900, +800), Vec2(-180, -108) },
	{ Vec2(+900, +720), Vec2(-200, +100) },
	{ Vec2(+900, +500), Vec2(-200, -100) },
	{ Vec2(+900, +400), Vec2(+200, -100) },
	{ Vec2(+900, +300), Vec2(-200, +100) },
	// ×óÉÏ½Ç
	{ Vec2(-100, 750), Vec2(900, -100) },
	{ Vec2(-100, 800), Vec2(900, -180) },
	{ Vec2(-100, 720), Vec2(900, -108) },
	{ Vec2(-100, 600), Vec2(900, -120) },
	{ Vec2(-100, 580), Vec2(900, -80)  },
	// ×óÏÂ½Ç
	{ Vec2(-180, -108), Vec2(+900, +800) },
	{ Vec2(-200, +100), Vec2(+900, +720) },
	{ Vec2(-200, -100), Vec2(+900, +500) },
	{ Vec2(+200, -100), Vec2(+900, +400) },
	{ Vec2(-200, +100), Vec2(+900, +300) },
	// ÓÒÏÂ½Ç
	{ Vec2(+900, +800), Vec2(-180, -108) },
	{ Vec2(+900, +720), Vec2(-200, +100) },
	{ Vec2(+900, +500), Vec2(-200, -100) },
	{ Vec2(+900, +400), Vec2(+200, -100) },
	{ Vec2(+900, +300), Vec2(-200, +100) },
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
	addChild(_fishSprite);
	//setAnchorPoint(Vec2(0.5f,0.5f));
	//_fishSprite->setAnchorPoint(this->getAnchorPoint());
	setContentSize(_fishSprite->getContentSize());
	this->playSwingAnimation();
	//dtawFishRect();
}

void Fish::destoryObject()
{
	this->stopAllActions();
}
void Fish::resetMe()
{}

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
	int maxType = 2;
	unsigned int randomType = cocos2d::random() % maxType;
	if (randomType == 0){
		moveWithDirPath();
	}
	else if (randomType == 1){
		moveWithAutoPath();
	}
	//else if (randomType == 2){
	//	moveWithCirclePath();
	//}
	//else if (randomType == 3){
	//	moveWithBezierPath();
	//}
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
{
	CircleBy* circle = CircleBy::create(Vec2(200,240), 10, 45, 1, true);
	this->runAction(circle);
}
void Fish::moveWithBezierPath()
{
	ccQuadBezierConfig bezier1;
	bezier1.controlPoint = Vec2(100, 200);
	bezier1.endPosition = Vec2(300, 0);
	auto action = CurveBy::create(10, bezier1);
	this->runAction(action);
}

void Fish::moveWithStraight(cocos2d::Vec2 startPos, cocos2d::Vec2 endedPos)
{
	// ÖØÖÃ½Ç¶È
	float angle = GameHelper::getAngle(startPos, endedPos);
	if ((0.0f > angle) && (angle >= -360.0f))
	{
		_fishSprite->setFlippedX(true);
	}
	this->setRotation(angle);
	this->setPosition(startPos);
	float distance = startPos.getDistance(endedPos);
	float duration = (distance / _fishInfo.fishSpeed);
	auto move = MoveTo::create(duration, endedPos);
	CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Fish::deleteMe, this));
	Sequence* sequence = Sequence::create(move, callFunc, nullptr);
	runAction(sequence);
}

void Fish::moveWithCircle(float duraction, cocos2d::Vec2 circleCenter, float radius, float angle)
{
}
void Fish::moveWithBezier()
{
}


int Fish::getExpByType()
{
	return _fishInfo.fishExp;
}
int Fish::getGoldByType()
{
	return _fishInfo.fishGold;
}
cocos2d::Sprite*Fish::getFishSprite()
{
	return _fishSprite;
}

cocos2d::Rect Fish::getCollisionRect()
{
	Vec2 origin = this->getBoundingBox().origin;
	Rect rect(0, 0, _contentSize.width * 0.5, _contentSize.height*0.5);
	return RectApplyAffineTransform(rect, this->getNodeToParentAffineTransform());
}
//void Fish::dtawFishRect()
//{
//	Rect box = this->getCollisionRect();
//	Rect box2 = box;
//	DrawNode* draw = DrawNode::create();
//	draw->setAnchorPoint(this->getAnchorPoint());
//	draw->drawRect(Vec2(box2.origin.x, box2.origin.y), Vec2(box2.size.width, box2.size.height), Color4F::RED);
//	addChild(draw);
//}

