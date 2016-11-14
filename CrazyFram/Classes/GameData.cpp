#include "GameData.h"
using namespace cocos2d;

GameData* GameData::_instance = nullptr;

GameData::GameData()
	:_golds(500)
	, _levelExp(0)
	, _lightExp(0)
	, _level(1)
	, _cannonType(0)
{}

GameData::~GameData()
{}

GameData* GameData::getInstance()
{
	if (!_instance)
	{
		_instance = new GameData();
	}
	return _instance;
}
void GameData::destoryInstance()
{
	delete _instance;
	_instance = nullptr;
}
int  GameData::getPlayerGold()
{
	return UserDefault::getInstance()->getIntegerForKey("PlayerGolds", _golds);
}

int  GameData::getPlayerLevelExp()
{
	return UserDefault::getInstance()->getIntegerForKey("LevelExp", _levelExp);
}

int  GameData::getLightLevelExp()
{
	return UserDefault::getInstance()->getIntegerForKey("LightExp", _lightExp);
}
int  GameData::getPlayerCurrcertLevel()
{
	return UserDefault::getInstance()->getIntegerForKey("PlayerLevel", _level);
}

int GameData::getCannonType()
{
	return UserDefault::getInstance()->getIntegerForKey("CannonType", _cannonType);
}

void GameData::savePlayerGold()
{
	UserDefault::getInstance()->setIntegerForKey("PlayerGolds", _golds);
	UserDefault::getInstance()->flush();
}
void GameData::savePlayerLevelExp()
{
	UserDefault::getInstance()->setIntegerForKey("LevelExp", _levelExp);
	UserDefault::getInstance()->flush();
}

void GameData::saveLightLevelExp()
{
	UserDefault::getInstance()->setIntegerForKey("LightExp", _lightExp);
	UserDefault::getInstance()->flush();
}

void GameData::savePlayerCurrcertLevel()
{
	UserDefault::getInstance()->setIntegerForKey("PlayerLevel", _level);
	UserDefault::getInstance()->flush();
}

void GameData::saveCannonType()
{
	UserDefault::getInstance()->setIntegerForKey("CannonType", _level);
	UserDefault::getInstance()->flush();
}