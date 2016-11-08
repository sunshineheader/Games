#include "FishLayer.h"
#include "Gold.h"
using namespace cocos2d;

Gold* Gold::create(FishLayer* layer)
{
	Gold* fish = new Gold();
	if (fish&&fish->init(layer))
	{
		fish->autorelease();
		return fish;
	}
	CC_SAFE_DELETE(fish);
	return nullptr;
}

bool Gold::init(FishLayer* layer)
{
	if (!BaseObject::init())
	{
		return false;
	}
	_fishLayer = layer;
	this->_initObject = std::bind(&Gold::initObject, this);
	this->_destoryObject = std::bind(&Gold::destoryObject, this);
	return true;
}

void Gold::initObject()
{}

void Gold::destoryObject()
{
	this->stopAllActions();
}