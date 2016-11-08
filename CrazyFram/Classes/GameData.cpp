#include "GameData.h"
using namespace cocos2d;

GameData* GameData::_instance = nullptr;

GameData::GameData()
	:_golds(500)
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

void GameData::savePlayerGold()
{
	UserDefault::getInstance()->setIntegerForKey("PlayerGolds", _golds);
	UserDefault::getInstance()->flush();
}
