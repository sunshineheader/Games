#include "GameData.h"
using namespace cocos2d;

GameData* GameData::_instance = nullptr;

GameData::GameData()
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