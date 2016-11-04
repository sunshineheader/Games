#include "Constants.h"
#include "GameScene.h"
#include "LoadingLayer.h"

Scene* LoadingLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingLayer::create();
	scene->addChild(layer);
	return scene;
}

LoadingLayer* LoadingLayer::create()
{
	LoadingLayer* layer = new LoadingLayer();
	if (layer && layer->init())
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool LoadingLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	this->_doEvent = std::bind(&LoadingLayer::doEvent, this);
	this->_doUI = std::bind(&LoadingLayer::doUI, this);
	this->_removeEvent = std::bind(&LoadingLayer::removeEvent, this);

	return true;
}

void LoadingLayer::doEvent()
{}

void LoadingLayer::doUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Text* loading = Text::create("Loading...","",24);
	loading->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(loading);


	_totalFiles = sizeof(PLIST_RESOURCES) / sizeof(PLIST_RESOURCES[0]);
	_currcertFile = 0;
	for (int i = 0; i < _totalFiles; i++)
	{
		std::string fileName = PLIST_RESOURCES[i] + ".png";
		TextureCache::getInstance()->addImageAsync(fileName, CC_CALLBACK_1(LoadingLayer::loadGameResourcesAsynchronous, this));
	}
}

void LoadingLayer::removeEvent()
{}

void LoadingLayer::loadGameResourcesAsynchronous(cocos2d::Texture2D* texture)
{
	std::string plistName = std::string(PLIST_RESOURCES[_currcertFile]) + ".plist";
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistName, texture);
	++_currcertFile;
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	if (_totalFiles == _currcertFile)
	{
		DelayTime* delay = DelayTime::create(0.5);
		CallFunc* callFunc = CallFunc::create([this]()
		{
			Director::getInstance()->replaceScene(GameScene::create());
		});

		Sequence* seq = Sequence::create(delay, callFunc, nullptr);
		this->runAction(seq);
	}
}
