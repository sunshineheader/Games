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

	FishLayer* fishLayer = FishLayer::create();
	MenuLayer* menuLayer = MenuLayer::create();
	return true;
}
