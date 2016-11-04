#include "MenuLayer.h"

MenuLayer* MenuLayer::create()
{
	MenuLayer* layer = new MenuLayer();
	if (layer && layer->init())
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool MenuLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	this->_doEvent = std::bind(&MenuLayer::doEvent, this);
	this->_doUI = std::bind(&MenuLayer::doUI, this);
	this->_removeEvent = std::bind(&MenuLayer::removeEvent, this);
	return true;
}

void MenuLayer::doEvent()
{}

void MenuLayer::doUI()
{}

void MenuLayer::removeEvent()
{}
