#include "InitLayerHeader.h"
#include "GameScene.h"


bool GameScene::init()
{
	if (!cocos2d::Scene::init())
	{
		return false;
	}

	BackgroundLayer* backgroundLayer = BackgroundLayer::create();
	addChild(backgroundLayer);

	_fishLayer = FishLayer::create(this);
	addChild(_fishLayer);
	_menuLayer = MenuLayer::create();
	addChild(_menuLayer);

	return true;
}

FishLayer*GameScene::getFishLayer()
{
	return _fishLayer;
}
MenuLayer*GameScene::getMenuLayer()
{
	return _menuLayer;
}