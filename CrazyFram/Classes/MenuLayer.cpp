#include "Cannon.h"
#include "GameScene.h"
#include "InitLayerHeader.h"

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
	this->_doEvent = std::bind(&MenuLayer::doEvent, this);
	this->_doUI = std::bind(&MenuLayer::doUI, this);
	this->_removeEvent = std::bind(&MenuLayer::removeEvent, this);
	return true;
}

void MenuLayer::doEvent()
{}

void MenuLayer::doUI()
{
	RESOURCE_NAME = "MenuLayer.csb";
	auto rootNode = CSLoader::createNode(RESOURCE_NAME);
	addChild(rootNode);

	// �ȼ����� 
	_levelText = static_cast<Text*>(GameHelper::seekNodeByName(rootNode,"level_text"));
	_levelLoadingBar = static_cast<LoadingBar*>(GameHelper::seekNodeByName(rootNode, "level_loading_bar"));
	// ÿ�����񲿷�
	Button* buyBtn = static_cast<Button*>(GameHelper::seekNodeByName(rootNode, "buy_button"));
	buyBtn->addClickEventListener(CC_CALLBACK_1(MenuLayer::buyButtonCallback, this));

	// ��������
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

	// �߱�ը������
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

	log("onTouchBegan");
	this->cannonAimAt(touch->getLocation());
	return false;
}

void MenuLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	log("onTouchMoved");
}
void MenuLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	log("onTouchEnded");
}

void MenuLayer::removeTouchEvent()
{
	this->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
}


void MenuLayer::createCannon()
{
	//TOOD��������ҵ���������ѡ��Ҫ����������
	_cannon = Cannon::create(this);
	_cannon->setPosition(Vec2(400,20));
	addChild(_cannon);
}
void MenuLayer::changeCannon()
{}

void MenuLayer::cannonAimAt(cocos2d::Vec2 location)
{
	// TOOD�� �ж��Ƿ���Է����ӵ�
	cocos2d::Vec2 cannonPos = _cannon->getPosition();
	_cannon->cannonAimat(location);
	// TOOD�� �Ƿ��Ǽ�������
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
	// TOOD��ˢ���߼�
	// �ȼ����� 

	// ÿ�����񲿷�
	
	// ��������
	
	// �߱�ը������
	// _cannon->setType(CannonType::CANNON_TYPE_07);
}