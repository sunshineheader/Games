#include "GameScene.h"
#include "InitLayerHeader.h"

PaymentLayer* PaymentLayer::create(GameScene* scene , PayType type)
{
	PaymentLayer* layer = new PaymentLayer();
	if (layer && layer->init(scene, type))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool PaymentLayer::init(GameScene* scene, PayType type)
{
	BaseLayer::init(scene);

	_type = type;
	this->_doEvent = std::bind(&PaymentLayer::doEvent, this);
	this->_doUI = std::bind(&PaymentLayer::doUI, this);
	this->_removeEvent = std::bind(&PaymentLayer::removeEvent, this);
	return true;
}

void PaymentLayer::doEvent()
{}

void PaymentLayer::doUI()
{
	if (_type == PayType::PAY_TYPE_00) {

	}
	else if (_type == PayType::PAY_TYPE_01){

	}
	else if (_type == PayType::PAY_TYPE_02){

	}
	else if (_type == PayType::PAY_TYPE_03){

	}
}

void PaymentLayer::removeEvent()
{}

void PaymentLayer::refreshUI()
{
	if (_type == PayType::PAY_TYPE_00) {

	}
	else if (_type == PayType::PAY_TYPE_01){

	}
	else if (_type == PayType::PAY_TYPE_02){

	}
	else if (_type == PayType::PAY_TYPE_03){

	}
	_GameScene->getMenuLayer()->refreshUI();
}
