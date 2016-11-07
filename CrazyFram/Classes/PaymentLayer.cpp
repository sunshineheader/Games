#include "PaymentLayer.h"
bool PaymentLayer::init(GameScene* scene)
{
	BaseLayer::init(scene);
	this->_doEvent = std::bind(&PaymentLayer::doEvent, this);
	this->_doUI = std::bind(&PaymentLayer::doUI, this);
	this->_removeEvent = std::bind(&PaymentLayer::removeEvent, this);
	return true;
}

void PaymentLayer::doEvent()
{}

void PaymentLayer::doUI()
{}

void PaymentLayer::removeEvent()
{}
