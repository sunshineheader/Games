#include "FishLayer.h"
#include "Lightting.h"
using namespace cocos2d;

Lightting*Lightting::create(FishLayer* layer, cocos2d::Vec2 location)
{
	Lightting* task = new Lightting();
	if (task && task->init(layer, location))
	{
		task->autorelease();
		return task;
	}
	CC_SAFE_DELETE(task);
	return nullptr;
}

bool Lightting::init(FishLayer* layer, cocos2d::Vec2 location)
{
	if (!BaseObject::init())
	{
		return false;
	}
	_fishLayer = layer;
	_location = location;
	this->_initObject = std::bind(&Lightting::initObject, this);
	this->_destoryObject = std::bind(&Lightting::destoryObject, this);
	return true;
}

void Lightting::initObject()
{
	_lightSprite = cocos2d::Sprite::createWithSpriteFrameName("Prop/0.png");
	addChild(_lightSprite);
	this->setPosition(Vec2(400,20));
	float distanceY = _location.y - this->getPosition().y;
	float distanceX = _location.x - this->getPosition().x;
	float radian = Vec2(distanceY, distanceX).getAngle();
	float angle = CC_RADIANS_TO_DEGREES(radian);
	this->setRotation(angle);
	this->setScale(2,5);
	_lightSprite->runAction(this->lightingAnimation());
	this->runAction(this->lightingAction());
}

void Lightting::destoryObject()
{}

cocos2d::Rect Lightting::getCollisionRect()
{
	CCPoint origin = this->getParent()->convertToWorldSpace(this->getPosition());
	CCSize defaultSize = _lightSprite->getContentSize();
	float scale = this->getScale();
	CCSize size = CCSizeMake(defaultSize.width*scale, defaultSize.height*scale);
	return CCRectMake(origin.x - size.width*0.5, origin.y - size.height*0.5, size.width, size.height);
}


cocos2d::Action* Lightting::lightingAnimation()
{
	Vector<SpriteFrame*>_animFrames;
	const int frames = 10;
	for (int i = 0; i < frames; i++)
	{
		std::string frameName = String::createWithFormat("Prop/%d.png", i)->_string;
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
		_animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(_animFrames, 0.1f);
	return RepeatForever::create(Animate::create(animation));
}

cocos2d::Action* Lightting::lightingAction()
{
	DelayTime* delta = DelayTime::create(0.5f);
	FadeOut* fadeOut = FadeOut::create(0.5f);
	CallFunc* callFunc = CallFunc::create([=](){
		this->removeFromParentAndCleanup(true);
	});
	return Sequence::create(delta, fadeOut, callFunc, nullptr);
}