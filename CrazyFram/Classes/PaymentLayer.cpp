#include "GameScene.h"
#include "InitLayerHeader.h"
#include "PayNodeFirst.h"
#include "PayNodeSecond.h"


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
	RESOURCE_NAME = "PaymentLayer.csb";
	auto rootNode = CSLoader::createNode(RESOURCE_NAME);
	addChild(rootNode);
	Layout* panel = static_cast<Layout*>(GameHelper::seekNodeByName(rootNode, "Panel_2"));
	if (_type == PayType::PAY_TYPE_00 || _type == PayType::PAY_TYPE_01) {
		PayNodeFirst* node = PayNodeFirst::create(this, _type);
		node->setPosition(Vec2(400, 240));
		panel->addChild(node);
	}
	else if (_type == PayType::PAY_TYPE_02 || _type == PayType::PAY_TYPE_03){
		PayNodeSceond* node = PayNodeSceond::create(this, _type);
		node->setPosition(Vec2(400, 240));
		panel->addChild(node);
	}
}

void PaymentLayer::removeEvent()
{}

void PaymentLayer::refreshUI()
{
	_GameScene->getMenuLayer()->refreshUI();
}
