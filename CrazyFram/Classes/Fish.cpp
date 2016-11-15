#include "CrazyFram.h"
#include "FishLayer.h"
#include "RotateWithAction.h"
#include "CircleBy.h"
#include "CurveBy.h"
#include "GameData.h"
#include "Fish.h"

using namespace cocos2d;

char*Fish::FISH_RESOURCES = "FishResource/Pic/0%d/%d_%d.png";

DirPath Fish::_DirPath[10] =
{
	// 左边
	{ Vec2(-100, 100), Vec2(900,  356),},
	{ Vec2(-112,  89), Vec2(911,  457),},
	{ Vec2(-134, 356), Vec2(732, -117),},
	{ Vec2(-94, 200), Vec2 (888,  333),},
	{ Vec2(-104, 480), Vec2(894,  104),},
	// 右边
	{ Vec2(+900,  100), Vec2(-100, 356), },
	{ Vec2(+912,  89), Vec2(-111, 457), },
	{ Vec2(+934,  356), Vec2(-132, -117), },
	{ Vec2(+894,  200), Vec2(-88, 333), },
	{ Vec2(+904,  480), Vec2(-108, 104), },
};

BezierPath Fish::_BezierPath[12] =
{
	// 左下角 ----->右上角
	{ cocos2d::Vec2(-10, 50), cocos2d::Vec2(400, 480), cocos2d::Vec2(400, 480), cocos2d::Vec2(810, 430), 12 },
	{ cocos2d::Vec2(-10, 50), cocos2d::Vec2(400, 480), cocos2d::Vec2(400, 0), cocos2d::Vec2(810, 430), 13 },
	{ cocos2d::Vec2(-10, 50), cocos2d::Vec2(400, 0), cocos2d::Vec2(400, 480), cocos2d::Vec2(810, 430), 14 },
	// 左上角 ----->右下角
	{ cocos2d::Vec2(-10, 430), cocos2d::Vec2(400, 480), cocos2d::Vec2(400, 480), cocos2d::Vec2(810, 50), 12 },
	{ cocos2d::Vec2(-10, 430), cocos2d::Vec2(400, 480), cocos2d::Vec2(400, 0), cocos2d::Vec2(810, 50), 13 },
	{ cocos2d::Vec2(-10, 430), cocos2d::Vec2(400, 0), cocos2d::Vec2(400, 480), cocos2d::Vec2(810, 50), 14 },
	// 右上角 ----->左下角
	{ cocos2d::Vec2(810, 430), cocos2d::Vec2(400, 480), cocos2d::Vec2(400, 480), cocos2d::Vec2(-10, 50), 12 },
	{ cocos2d::Vec2(810, 430), cocos2d::Vec2(400, 480), cocos2d::Vec2(400, 0), cocos2d::Vec2(-10, 50), 13 },
	{ cocos2d::Vec2(810, 430), cocos2d::Vec2(400, 0), cocos2d::Vec2(400, 480), cocos2d::Vec2(-10, 50), 14 },

	// 右下角 ----->左上角
	{ cocos2d::Vec2(810, 50), cocos2d::Vec2(400, 480), cocos2d::Vec2(400, 480), cocos2d::Vec2(-10, 430), 12 },
	{ cocos2d::Vec2(810, 50), cocos2d::Vec2(400, 480), cocos2d::Vec2(400, 0), cocos2d::Vec2(-10, 430), 13 },
	{ cocos2d::Vec2(810, 50), cocos2d::Vec2(400, 0), cocos2d::Vec2(400, 480), cocos2d::Vec2(-10, 430), 14 },
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
	if (!BaseObject::init()) {
		return false;
	}
	_fishLayer = layer;
	_fishInfo = info;
	_isCatched = false;
	this->_initObject = std::bind(&Fish::initObject, this);
	this->_destoryObject = std::bind(&Fish::destoryObject, this);
	return true;
}

void Fish::initObject()
{
	float scalar = 1.0f;
	if (_fishInfo.fishType == FishType::FISH_TYPE_10){
		const std::string fishName = "Prop/propRedPaper.png";
		_fishSprite = cocos2d::Sprite::createWithSpriteFrameName(fishName);
		addChild(_fishSprite);
		setContentSize(_fishSprite->getContentSize()*scalar);
	}
	else if (_fishInfo.fishType == FishType::FISH_TYPE_11) {
		const std::string fishName = "Prop/propFish.png";
		_fishSprite = cocos2d::Sprite::createWithSpriteFrameName(fishName);
		addChild(_fishSprite);
		setContentSize(_fishSprite->getContentSize()*scalar);
	}
	else {
		const std::string fishName = String::createWithFormat(FISH_RESOURCES, _fishInfo.fishType, _fishInfo.fishType, 0)->_string;
		_fishSprite = cocos2d::Sprite::createWithSpriteFrameName(fishName);
		addChild(_fishSprite);
		setContentSize(_fishSprite->getContentSize()*scalar);
		this->playSwingAnimation();
	}
}

void Fish::destoryObject()
{
	this->stopAllActions();
	if (_isCatched) {
		// 刷新界面
		// 金币
		int coin = GameData::getInstance()->getPlayerGold();
		coin = coin + _fishInfo.fishGold;
		GameData::getInstance()->setPlayerGold(coin);
		GameData::getInstance()->savePlayerGold();
		// 经验
		int exp = GameData::getInstance()->getPlayerLevelExp();
		exp = exp + _fishInfo.fishExp;
		GameData::getInstance()->setPlayerLevelExp(exp);
		GameData::getInstance()->savePlayerLevelExp();
		//// 激光
		int light = GameData::getInstance()->getLightLevelExp();
		light = light + _fishInfo.fishLight;
		GameData::getInstance()->setLightLevelExp(light);
		GameData::getInstance()->saveLightLevelExp();	
		_fishLayer->refreshUI();
	}
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
	_isCatched = true;
	if (_isCatched)
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
}

void Fish::move()
{
	int maxType = 3;
	unsigned int randomType = cocos2d::random() % maxType;
	if (randomType == 0){
		moveWithAutoPath();
	}
	else if (randomType == 1){
		moveWithAutoPath();
	}
	else if (randomType == 2){
		moveWithBezierPath();
	}
	//else if (randomType == 3){
	//	moveWithCirclePath();
	//}
}

void Fish::moveWithDirPath()
{
	unsigned int randomType = cocos2d::random() % 10;
	if (randomType < 6) {
		this->moveWithStraight(false ,_DirPath[randomType].startPos, _DirPath[randomType].endedPos);
	}
	else {
		this->moveWithStraight(true , _DirPath[randomType].startPos, _DirPath[randomType].endedPos);
	}
}

void Fish::moveWithAutoPath()
{
	bool direction = std::abs(std::rand() % 2) == 1;
	Vec2 satrtPos, endedPos;
	Size fishSize = _fishSprite->getContentSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float radius = (fishSize.width > fishSize.height ? fishSize.width : fishSize.height) / 2;
	if (!direction) {
		satrtPos.x = -radius;
		satrtPos.y = rand() % (int)visibleSize.height + radius;
		endedPos.x = visibleSize.width + radius;
		endedPos.y = rand() % (int)visibleSize.height;
	}
	else{
		satrtPos.x = visibleSize.width + radius;
		satrtPos.y = rand() % (int)visibleSize.height + radius;
		endedPos.x = -radius;
		endedPos.y = rand() % (int)visibleSize.height;
	}
	this->moveWithStraight(direction,satrtPos, endedPos);
}

void Fish::moveWithBezierPath() {
	auto randomType = cocos2d::random() % 12;
	this->moveWithBezierPathByPathType(randomType);
}

void Fish::moveWithBezierPathByPathType(int type) {
	BezierPath bezier = _BezierPath[type];
	if (type >= 6) {
		this->moveWithBezier(true, bezier.startPosition, bezier.controlPoint1, bezier.controlPoint2, bezier.ebdedPosition, bezier.time);
	}
	else {
		this->moveWithBezier(false, bezier.startPosition, bezier.controlPoint1, bezier.controlPoint2, bezier.ebdedPosition, bezier.time);
	}
}


void Fish::moveWithStraight(bool direction, cocos2d::Vec2 startPos, cocos2d::Vec2 endedPos) {
	// 重置角度
	_fishSprite->setFlipX(direction);
	float distanceY = endedPos.y - startPos.y;
	float distanceX = endedPos.x - startPos.x;
	float radian = Vec2(distanceY, distanceX).getAngle();
	float angle = CC_RADIANS_TO_DEGREES(radian);
	if (!direction) { 
		angle -= 90.0f;
	}
	else {	
		angle += 90.0f;	
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



void Fish::moveWithBezier(bool direction, cocos2d::Vec2 startPos, cocos2d::Vec2  controlPoint1, cocos2d::Vec2  controlPoint2, cocos2d::Vec2 endedPos, float time)
{
	_fishSprite->setFlipX(direction);
	this->setPosition(startPos);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto midPos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height);
	ccBezierConfig config;
	config.controlPoint_1 = controlPoint1;
	config.controlPoint_2 = controlPoint2;
	config.endPosition = endedPos;
	BezierTo* bezier = BezierTo::create(time, config);
	EaseRateAction*ease = EaseRateAction::create(bezier, time);
	CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Fish::deleteMe, this));
	Sequence* sequence = Sequence::create(ease, callFunc, nullptr);
	RotateWithAction* rotate = RotateWithAction::create(sequence);
	this->runAction(rotate);
}

int Fish::getType()
{
	return _fishInfo.fishType;
}

int Fish::getExpByType()
{
	return _fishInfo.fishExp;
}

int Fish::getGoldByType()
{
	return _fishInfo.fishGold;
}

cocos2d::Rect Fish::getCollisionRect()
{
	CCAssert(this->getParent(), "You Should Call This After Add it as a child");
	float saclar = 1;
	CCPoint origin = this->getParent()->convertToWorldSpace(this->getPosition());
	CCSize size = _fishSprite->getContentSize() * saclar;
	return CCRectMake(origin.x - size.width*0.5, origin.y - size.height*0.5, size.width, size.height);
}


//void Fish::moveWithBezier(cocos2d::Vec2 form, cocos2d::Vec2 to, float time, bool direction)
//{
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	float h[] = { 55.0, visibleSize.height - 10.0f };
//	float r[] = { h[1] - h[0] / 2, - h[1] - h[0] / 2 };
//	_fishSprite->setFlippedX(direction);
//	ccBezierConfig config1, config2;
//	config1.controlPoint_1 = config1.controlPoint_2 = cocos2d::Vec2(visibleSize.width/2+r[!direction]/3,h[direction]);
//	config1.endPosition = cocos2d::Vec2(visibleSize.width / 2, h[0] + r[0]);
//	config2.controlPoint_1 = config2.controlPoint_2 = cocos2d::Vec2(visibleSize.width / 2 + r[direction] / 3, h[!direction]);
//	config2.endPosition = cocos2d::Vec2(visibleSize.width / 2, h[!direction]);
//	Sequence* moveSeqence = Sequence::create(
//		MoveTo::create(time / 4, cocos2d::Vec2(visibleSize.width / 2 + r[direction], h[!direction])),
//		BezierTo::create(time / 4, config1),
//		BezierTo::create(time / 4, config2),
//		MoveTo::create(time / 4, to),
//		nullptr);
//	EaseRateAction* action = EaseRateAction::create(moveSeqence,1);
//	EaseBezierAction * ber = EaseBezierAction::create(moveSeqence);
//	RotateWithAction* ratate = RotateWithAction::create(action);
//
//	this->runAction(ratate);
//}