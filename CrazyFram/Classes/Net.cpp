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
}

void Net::destoryObject()
{
	this->stopAllActions();
}