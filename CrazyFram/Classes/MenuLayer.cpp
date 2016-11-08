#include "Cannon.h"
#include "GameScene.h"
#include "GameData.h"
#include "InitLayerHeader.h"


static CannonData cannontData[8]
{
	{ CannonType(0), 1 },
	{ CannonType(1), 2 },
	{ CannonType(2), 3 },
	{ CannonType(3), 4 },
	{ CannonType(4), 5 },
	{ CannonType(5), 10 },
	{ CannonType(6), 20 },
	{ CannonType(7), 0 },
};

MenuLayer* MenuLayer::create(GameScene* scene)
{
	MenuLayer* layer = new MenuLayer();
	if (layer && layer->init(scene))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool MenuLayer::init(GameScene* scene)
{
	BaseLayer::init(scene);

	_touchEnable = true;
	this->_doEvent = std::bind(&MenuLayer::doEvent, this);
	this->_doUI = std::bind(&MenuLayer::doUI, this);
	this->_removeEvent = std::bind(&MenuLayer::removeEvent, this);
	const std::string name = UserDefault::getInstance()->getXMLFilePath();
	return true;
}

void MenuLayer::doEvent()
{}

void MenuLayer::doUI()
{
	RESOURCE_NAME = "MenuLayer.csb";
	auto rootNode = CSLoader::createNode(RESOURCE_NAME);
	addChild(rootNode);

	// 等级部分 
	_levelText = static_cast<Text*>(GameHelper::seekNodeByName(rootNode,"level_text"));
	_levelLoadingBar = static_cast<LoadingBar*>(GameHelper::seekNodeByName(rootNode, "level_loading_bar"));
	// 每日任务部分
	Button* buyBtn = static_cast<Button*>(GameHelper::seekNodeByName(rootNode, "buy_button"));
	buyBtn->addClickEventListener(CC_CALLBACK_1(MenuLayer::buyButtonCallback, this));

	// 炮塔部分
	Button* boxBtn = static_cast<Button*>(GameHelper::seekNodeByName(rootNode, "box"));
	boxBtn->addClickEventListener(CC_CALLBACK_1(MenuLayer::boxButtonCallback, this));
	_goldText = static_cast<Text*>(GameHelper::seekNodeByName(rootNode, "gold_text"));

	Button* subBtn = static_cast<Button*>(GameHelper::seekNodeByName(rootNode, "sub_button"));
	subBtn->addClickEventListener(CC_CALLBACK_1(MenuLayer::subButtonCallback, this));

	Button* addBtn = static_cast<Button*>(GameHelper::seekNodeByName(rootNode, "add_button"));
	addBtn->addClickEventListener(CC_CALLBACK_1(MenuLayer::addButtonCallback, this));

	_lightLoadingBar = static_cast<LoadingBar*>(GameHelper::seekNodeByName(rootNode, "light_exp_loading_bar"));
	
	Button* setBtn = static_cast<Button*>(GameHelper::seekNodeByName(rootNode, "setting"));
	setBtn->addClickEventListener(CC_CALLBACK_1(MenuLayer::setButtonCallback, this));

	// 高爆炸弹部分
	Button* boombBtn = static_cast<Button*>(GameHelper::seekNodeByName(rootNode, "boomb_button"));
	boombBtn->addClickEventListener(CC_CALLBACK_1(MenuLayer::bmbButtonCallback, this));
	_boombText = static_cast<Text*>(GameHelper::seekNodeByName(rootNode, "boomb_text"));

	createCannon();
	addTouchEvent();
	refreshUI();
}

void MenuLayer::removeEvent()
{
	removeTouchEvent();
}

void MenuLayer::addTouchEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MenuLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MenuLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MenuLayer::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool MenuLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (_touchEnable)
	{
		if (_cannon->getType() == CannonType::CANNON_TYPE_07) 
		{
			this->createLighting(touch->getLocation());
		}
		else 
		{
			if (this->checkCoin()) 
			{
				this->cannonAimAt(touch->getLocation());
			}
			else
			{
				this->changeCannon();
			}
		}
	}
	return false;
}

void MenuLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{}

void MenuLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{}

void MenuLayer::removeTouchEvent()
{
	this->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
}


void MenuLayer::createCannon()
{
	//TOOD：根据玩家的炮塔类型选择要创建的炮塔
	_cannon = Cannon::create(this);
	_cannon->setPosition(Vec2(400,20));
	addChild(_cannon);
}
// 检查金币
bool MenuLayer::checkCoin()
{
	// TOOD： 判断是否可以发射子弹
	int coin = GameData::getInstance()->getPlayerGold();
	if (coin == 0){
		// TOOD： 奖励500金币
		return false;
	}else if (coin >= cannontData[_cannon->getType()].cannonPrice) {
		coin = coin - cannontData[_cannon->getType()].cannonPrice;
		GameData::getInstance()->setPlayerGold(coin);
		GameData::getInstance()->savePlayerGold();
		refreshUI();
		return true;
	}
	return false;
}
// 改变炮塔
void MenuLayer::changeCannon()
{
	int coin = GameData::getInstance()->getPlayerGold();
	int type = _cannon->getType();
	int prevType = type - 1;
	if (prevType >= 0)
	{
		if (coin >= cannontData[prevType].cannonPrice){
			_cannon->setType(CannonType(prevType));
		}
		else {
			_cannon->setType(CannonType(prevType));
			changeCannon();
		}
	}
}

void MenuLayer::cannonAimAt(cocos2d::Vec2 location)
{
	cocos2d::Vec2 cannonPos = _cannon->getPosition();
	_cannon->cannonAimat(location);
	// TOOD： 是否是激光类型
	if (_cannon->getType() == CannonType::CANNON_TYPE_07 ){
		this->createLighting(location);
	}else{
		int type =_cannon->getType();
		this->createBullet(location, type);
	}
}

void MenuLayer::createBullet(cocos2d::Vec2 position, int type)
{
	_GameScene->getFishLayer()->createBulletAt(position, type);
}

void MenuLayer::createLighting(cocos2d::Vec2 position)
{
	_GameScene->getFishLayer()->createLightingAt(position);
}

void MenuLayer::buyButtonCallback(cocos2d::Ref* sender)
{}

void MenuLayer::boxButtonCallback(cocos2d::Ref* sender)
{}

void MenuLayer::addButtonCallback(cocos2d::Ref* sender)
{
	int MAX_CANNON_TYPE = 6;
	int curType = (int)(_cannon->getType());
	int nextType = curType + 1;
	if (nextType <= MAX_CANNON_TYPE){
		_cannon->setType(CannonType(nextType));
	}else{
		nextType = 0;
		_cannon->setType(CannonType(nextType));
	}

}
void MenuLayer::subButtonCallback(cocos2d::Ref* sender)
{
	int MAX_CANNON_TYPE = 6;
	int curType = (int)(_cannon->getType());
	int prevType = curType - 1;
	if (prevType >= 0){
		_cannon->setType(CannonType(prevType));
	}
	else{
		prevType = 6;
		_cannon->setType(CannonType(prevType));
	}
}
void MenuLayer::setButtonCallback(cocos2d::Ref* sender)
{
}
void MenuLayer::bmbButtonCallback(cocos2d::Ref* sender)
{}

void MenuLayer::refreshUI()
{
	// TOOD：刷新逻辑
	// 等级部分 
	
	// 每日任务部分
	
	// 炮塔部分
	int coin = GameData::getInstance()->getPlayerGold();
	_goldText->setString(String::createWithFormat("%d", coin)->_string);

    // light
	float percent = 100.0f;
	_lightLoadingBar->setPercent(percent);
	if (percent == 100.0f)
	{
		_cannon->setType(CannonType::CANNON_TYPE_07);
	}
	// 高爆炸弹部分
}

void MenuLayer::setTouchedEnable(bool enable)
{
	_touchEnable = enable;
}