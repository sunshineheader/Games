#include "InitLayerHeader.h"
#include "GameData.h"
#include "PayNodeSecond.h"


PayNodeSceond* PayNodeSceond::create(PaymentLayer* layer, int type)
{
	PayNodeSceond* node = new PayNodeSceond();
	if (node && node->init(layer, type))
	{
		node->autorelease();
		return node;
	}
	CC_SAFE_DELETE(node);
	return nullptr;
}

bool PayNodeSceond::init(PaymentLayer* layer, int type)
{
	if (!BaseObject::init()) {
		return false;
	}
	_layer = layer;
	_type = type;
	_isBuy = false;
	this->_initObject = std::bind(&PayNodeSceond::initObject, this);
	this->_destoryObject = std::bind(&PayNodeSceond::destoryObject, this);
	return true;
}

void PayNodeSceond::initObject()
{
	const std::string RESOURCE_NAME = "PayType01.csb";
	auto rootNode = CSLoader::createNode(RESOURCE_NAME);
	addChild(rootNode);
	ImageView* title = static_cast<ImageView*>(GameHelper::seekNodeByName(rootNode, "title_image"));
	ImageView* props1 = static_cast<ImageView*>(GameHelper::seekNodeByName(rootNode, "prop_1"));
	ImageView* props2 = static_cast<ImageView*>(GameHelper::seekNodeByName(rootNode, "prop_2"));
	Text* text1 = static_cast<Text*>(GameHelper::seekNodeByName(rootNode, "Text_1"));
	Text* text2 = static_cast<Text*>(GameHelper::seekNodeByName(rootNode, "Text_2"));
	if (_type == 2) {
		_prop1Num = 2000;
		_prop2Num = 5;
		title->setVisible(false);
		props1->loadTexture("Game/Pic/gold_.png", cocos2d::ui::Widget::TextureResType::PLIST);
		props2->loadTexture("Game/Pic/boombBullet.png", cocos2d::ui::Widget::TextureResType::PLIST);
		text1->setString(String::createWithFormat("%d", _prop1Num)->_string);
		text2->setString(String::createWithFormat("%d", _prop2Num)->_string);
	}
	else{
		_prop1Num = 1500;
		_prop2Num = 2;
		title->loadTexture("Game/Pic/daoju_title.png", cocos2d::ui::Widget::TextureResType::PLIST);
		props1->loadTexture("Game/Pic/gold_.png", cocos2d::ui::Widget::TextureResType::PLIST);
		props2->loadTexture("Game/Pic/boombBullet.png", cocos2d::ui::Widget::TextureResType::PLIST);
		text1->setString(String::createWithFormat("%d", _prop1Num)->_string);
		text2->setString(String::createWithFormat("%d", _prop2Num)->_string);
	}

	Button* closeBtn = static_cast<Button*>(GameHelper::seekNodeByName(rootNode, "closeBtn"));
	closeBtn->addClickEventListener(CC_CALLBACK_1(PayNodeSceond::closeBtnCallBack, this));
	Button* buyBtn = static_cast<Button*>(GameHelper::seekNodeByName(rootNode, "buyBtn"));
	buyBtn->addClickEventListener(CC_CALLBACK_1(PayNodeSceond::buyBtnCallBack, this));
}
void PayNodeSceond::destoryObject()
{
	if (_isBuy) {
		int coin = GameData::getInstance()->getPlayerGold();
		coin += _prop1Num;
		GameData::getInstance()->setPlayerGold(coin);
		GameData::getInstance()->savePlayerGold();

		int boombs = GameData::getInstance()->getBoombs();
		boombs += _prop2Num;
		GameData::getInstance()->setBoombs(boombs);
		GameData::getInstance()->saveBoombs();

		_layer->refreshUI();
	}
}
void PayNodeSceond::closeBtnCallBack(cocos2d::Ref* ref)
{
	_layer->removeFromParentAndCleanup(true);
}
void PayNodeSceond::buyBtnCallBack(cocos2d::Ref* ref)
{
	_isBuy = true; // 
	_layer->removeFromParentAndCleanup(true);
}
