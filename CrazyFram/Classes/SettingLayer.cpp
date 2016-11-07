#include "SettingLayer.h"
bool SettingLayer::init(GameScene* scene)
{
	BaseLayer::init(scene);
	this->_doEvent = std::bind(&SettingLayer::doEvent, this);
	this->_doUI = std::bind(&SettingLayer::doUI, this);
	this->_removeEvent = std::bind(&SettingLayer::removeEvent, this);
	return true;
}

void SettingLayer::doEvent()
{}

void SettingLayer::doUI()
{}

void SettingLayer::removeEvent()
{}
