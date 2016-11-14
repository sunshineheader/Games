#include "InitLayerHeader.h"
#include "GameData.h"
#include "PayNodeFirst.h"

PayNodeFirst* PayNodeFirst::create(PaymentLayer* layer, int type)
{
	PayNodeFirst* node = new PayNodeFirst();
	if (node && node->init(layer, type))
	{
		node->autorelease();
		return node;
	}
	CC_SAFE_DELETE(node);
	return nullptr;
}

bool PayNodeFirst::init(PaymentLayer* layer, int type)
{
	if (!BaseObject::init()) {
		return false;
	}
	_layer = layer;
	_type = type;
	_isBuy = false;
	this->_initObject = std::bind(&PayNodeFirst::initObject, this);
	this->_destoryObject = std::bind(&PayNodeFirst::destoryObject, this);
	return true;
}

void PayNodeFirst::initObject()
{
	const std::string RESOURCE_NAME = "PayType00.csb";
	auto rootNode = CSLoader::createNode(RESOURCE_NAME);
	addChild(rootNode);

	ImageView* title = static_cast<ImageView*>(GameHelper::seekNodeByName(rootNode, "title_image"));
	ImageView* props = static_cast<ImageView*>(GameHelper::seekNodeByName(rootNode, "Image_3"));
	Text* text = static_cast<Text*>(GameHelper::seekNodeByName(rootNode, "Text_01"));
	if (_type == 0) {
		_propNum = 4;
		title->loadTexture("Game/Pic/boomb_title.png", cocos2d::ui::Widget::TextureResType::PLIST);
		props->loadTexture("Game/Pic/boombBullet.png", cocos2d::ui::Widget::TextureResType::PLIST);
		text->setString(String::createWithFormat("%d",_propNum)->_string);
	}
	else{
		_propNum = 2500;
		title->loadTexture("Game/Pic/gold_title.png", cocos2d::ui::Widget::TextureResType::PLIST);
		props->loadTexture("Game/Pic/gold_.png", cocos2d::ui::Widget::TextureResType::PLIST);
		text->setString(String::createWithFormat("%d", _propNum)->_string);
	}

	Button* closeBtn = static_cast<Button*>(GameHelper::seekNodeByName(rootNode, "closeBtn"));
	closeBtn->addClickEventListener(CC_CALLBACK_1(PayNodeFirst::closeBtnCallBack, this));
	Button* buyBtn = static_cast<Button*>(GameHelper::seekNodeByName(rootNode, "buyBtn"));
	buyBtn->addClickEventListener(CC_CALLBACK_1(PayNodeFirst::buyBtnCallBack, this));
}
void PayNodeFirst::destoryObject()
{
	if (_isBuy) {
		if (_type == 0){
			int boombs = GameData::getInstance()->getBoombs();
			boombs += _propNum;
			GameData::getInstance()->setBoombs(boombs);
			GameData::getInstance()->saveBoombs();
		}
		else {
			int coin = GameData::getInstance()->getPlayerGold();
			coin += _propNum;
			GameData::getInstance()->setPlayerGold(coin);
			GameData::getInstance()->savePlayerGold();
		}
		_layer->refreshUI();
	}
}
void PayNodeFirst::closeBtnCallBack(cocos2d::Ref* ref)
{
	_layer->removeFromParentAndCleanup(true);
}
void PayNodeFirst::buyBtnCallBack(cocos2d::Ref* ref)
{
	_isBuy = true; // 
	_layer->removeFromParentAndCleanup(true);
}
