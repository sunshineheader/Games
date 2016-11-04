#include "FishLayer.h"

FishLayer* FishLayer::create()
{
	FishLayer* layer = new FishLayer();
	if (layer && layer->init())
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool FishLayer::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}

	this->_doEvent = std::bind(&FishLayer::doEvent, this);
	this->_doUI = std::bind(&FishLayer::doUI, this);
	this->_removeEvent = std::bind(&FishLayer::removeEvent, this);

	return true;
}

void FishLayer::doEvent()
{}

void FishLayer::doUI()
{}

void FishLayer::removeEvent()
{}
