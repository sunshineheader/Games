#include "SettingLayer.h"

SettingLayer* SettingLayer::create(GameScene* scene)
{
	SettingLayer* layer = new SettingLayer();
	if (layer && layer->init(scene))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

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
{
	RESOURCE_NAME = "SettingLayer.csb";
	auto rootNode = CSLoader::createNode(RESOURCE_NAME);
	addChild(rootNode);
    Layout* panel = static_cast<Layout*>(GameHelper::seekNodeByName(rootNode, "Panel_2"));
	panel->addClickEventListener(CC_CALLBACK_1(SettingLayer::panelClickCallBack, this));

}

void SettingLayer::removeEvent()
{}

void SettingLayer::panelClickCallBack(cocos2d::Ref* ref)
{
	this->removeFromParentAndCleanup(true);
}