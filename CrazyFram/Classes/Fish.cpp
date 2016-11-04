#include "Fish.h"
using namespace cocos2d;

Fish* Fish::create()
{
	Fish* fish = new Fish();
	if (fish&&fish->init())
	{
		fish->autorelease();
		return fish;
	}
	CC_SAFE_DELETE(fish);
	return nullptr;
}

bool Fish::init()
{
	if (!BaseObject::init())
	{
		return false;
	}

	this->_initObject = std::bind(&Fish::initObject, this);
	this->_destoryObject = std::bind(&Fish::destoryObject, this);

	return true;
}


void Fish::initObject()
{}

void Fish::destoryObject()
{}

void Fish::move()
{}
void Fish::moveWithDirPath()
{}
void Fish::moveWithAutoPath()
{}
void Fish::moveWithCirclePath()
{}
void Fish::moveWithBezierPath()
{}



