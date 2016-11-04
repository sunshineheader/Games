#include "BackgroundLayer.h"

BackgroundLayer* BackgroundLayer::create()
{
	BackgroundLayer* layer = new BackgroundLayer();
	if (layer && layer->init())
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}


bool BackgroundLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}
	this->_doEvent = std::bind(&BackgroundLayer::doEvent, this);
	this->_doUI = std::bind(&BackgroundLayer::doUI, this);
	this->_removeEvent = std::bind(&BackgroundLayer::removeEvent, this);
	return true;
}

void BackgroundLayer::doEvent()
{}

void BackgroundLayer::doUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	ImageView* background = ImageView::create("bg.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background);
}

void BackgroundLayer::removeEvent()
{}
