#include "Fish.h"
#include "GameScene.h"
#include "FishLayer.h"

FishLayer* FishLayer::create(GameScene* scene)
{
	FishLayer* layer = new FishLayer();
	if (layer && layer->init(scene))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool FishLayer::init(GameScene* scene)
{
	BaseLayer::init(scene);

	// init fish pool
	_fishPool.reserve(4);


	this->_doEvent = std::bind(&FishLayer::doEvent, this);
	this->_doUI = std::bind(&FishLayer::doUI, this);
	this->_removeEvent = std::bind(&FishLayer::removeEvent, this);

	return true;
}

void FishLayer::doEvent()
{}

void FishLayer::doUI()
{
	createFish();
}

void FishLayer::removeEvent()
{}

void FishLayer::createFish()
{}

void FishLayer::createFishWithSigine()
{}

void FishLayer::createFishWithMore()
{}

void FishLayer::createFishWithType()
{}

void FishLayer::removeFishSigine(Fish* fish)
{}


void FishLayer::checkOutCollision()
{
	bool falg = this->checkOutCollisionBetweenFishesAndBullet();
	if (falg)
	{
		this->checkOutCollisionBetweenFishesAndFishingNet();
	}
}
bool FishLayer::checkOutCollisionBetweenFishesAndBullet()
{
	return true;
}
void FishLayer::checkOutCollisionBetweenFishesAndFishingNet()
{}