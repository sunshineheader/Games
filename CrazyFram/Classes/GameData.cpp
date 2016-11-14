#include "GameData.h"
using namespace cocos2d;

GameData* GameData::_instance = nullptr;

GameData::GameData()
	:_bgMusic(true)
	, _effectMusic(true)
	,_golds(500)
	, _levelExp(0)
	, _lightExp(0)
	, _level(1)
	, _cannonType(0)
	, _boombs(1)
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

bool  GameData::getMusicStatus()
{
	return UserDefault::getInstance()->getBoolForKey("BgMusic", _bgMusic);
}

bool  GameData::getEffectStatus()
{
	return UserDefault::getInstance()->getBoolForKey("Effects", _effectMusic);
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

int GameData::getBoombs()
{
	return UserDefault::getInstance()->getIntegerForKey("BoombNumber", _boombs);
}

void GameData::saveMusicStatus()
{
	UserDefault::getInstance()->setBoolForKey("BgMusic", _bgMusic);
	UserDefault::getInstance()->flush();
}
void GameData::saveEffectStatus()
{
	UserDefault::getInstance()->setBoolForKey("Effects", _effectMusic);
	UserDefault::getInstance()->flush();
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
	UserDefault::getInstance()->setIntegerForKey("CannonType", _cannonType);
	UserDefault::getInstance()->flush();
}

void GameData::saveBoombs()
{
	UserDefault::getInstance()->setIntegerForKey("BoombNumber", _boombs);
	UserDefault::getInstance()->flush();
}
