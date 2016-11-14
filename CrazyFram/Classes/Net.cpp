#include "FishLayer.h"
#include "Net.h"
using namespace cocos2d;

Net* Net::create(FishLayer* layer, NetType type)
{
	Net* fish = new Net();
	if (fish&&fish->init(layer, type))
	{
		fish->autorelease();
		return fish;
	}
	CC_SAFE_DELETE(fish);
	return nullptr;
}

bool Net::init(FishLayer* layer, NetType type)
{
	if (!BaseObject::init())
	{
		return false;
	}

	_fishLayer = layer;
	_type = type;
	this->_initObject = std::bind(&Net::initObject, this);
	this->_destoryObject = std::bind(&Net::destoryObject, this);
	return true;
}

void Net::initObject()
{
	const std::string netName = String::createWithFormat("net0%d.png", _type + 1)->_string;
	_netSprite = Sprite::createWithSpriteFrameName(netName);
	addChild(_netSprite);
	this->runAction(this->netAction());
}

void Net::destoryObject()
{
	this->stopAllActions();
}

void Net::deleteMe()
{
	_fishLayer->removeNetSigine(this);
}

cocos2d::Action* Net::netAction()
{
	DelayTime* delay = DelayTime::create(1.0);
	Hide* hide = Hide::create();
	CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Net::deleteMe, this));
	return Sequence::create(delay, hide, callFunc, nullptr);
}


Rect Net::getCollisionRect()
{
	// TOOD:·µ»ØÅö×²ÇøÓò
	CCPoint origin = this->getParent()->convertToWorldSpace(this->getPosition());
	CCSize defaultSize = _netSprite->getContentSize();
	float scale = this->getScale();
	CCSize size = CCSizeMake(defaultSize.width*scale, defaultSize.height*scale);
	return CCRectMake(origin.x - size.width*0.5, origin.y - size.height*0.5, size.width, size.height);
}
