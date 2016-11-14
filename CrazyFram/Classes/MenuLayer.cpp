#include "CrazyFram.h"
#include "GameScene.h"
#include "GameData.h"
#include "InitObjectHeader.h"
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
	createTask(10);
	// schedule(schedule_selector(MenuLayer::createTask), 180.0f, CC_REPEAT_FOREVER, 0.0f);

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
	if (_touchEnable) {
		if (_cannon->getType() == CannonType::CANNON_TYPE_07) {
			this->cannonAimAt(touch->getLocation());
			this->createLighting(touch->getLocation());
		}
		else {
			if (this->checkCoin()) {
				this->cannonAimAt(touch->getLocation());
			}
			else{
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
void MenuLayer::createTask(float delta) {

	Task* task = Task::create(this);
	task->setPosition(120, 360);
	addChild(task);
}
void MenuLayer::createCannon()
{
	//TOOD��������ҵ���������ѡ��Ҫ����������
	int cannonType = GameData::getInstance()->getCannonType();
	_cannon = Cannon::create(this, CannonType(cannonType));
	_cannon->setPosition(Vec2(400,20));
	addChild(_cannon);
	GameData::getInstance()->setCannonType(cannonType);
	GameData::getInstance()->saveCannonType();

}
// �����
bool MenuLayer::checkCoin()
{
	// TOOD�� �ж��Ƿ���Է����ӵ�
	int coin = GameData::getInstance()->getPlayerGold();
	if (coin == 0){
		// TOOD�� ����500���
		coin = 500;
		this->createGoldAt(true);
		GameData::getInstance()->setPlayerGold(coin);
		GameData::getInstance()->savePlayerGold();
		refreshUI();
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
// �ı�����
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
{
	PaymentLayer* payLayer = PaymentLayer::create(_GameScene, PayType(2));
	_GameScene->addChild(payLayer, 10);
}

void MenuLayer::boxButtonCallback(cocos2d::Ref* sender)
{
	PaymentLayer* payLayer = PaymentLayer::create(_GameScene, PayType(1));
	_GameScene->addChild(payLayer, 10);
}

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
	GameData::getInstance()->setCannonType(nextType);
	GameData::getInstance()->saveCannonType();

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
	GameData::getInstance()->setCannonType(prevType);
	GameData::getInstance()->saveCannonType();
}
void MenuLayer::setButtonCallback(cocos2d::Ref* sender)
{
	SettingLayer* setting = SettingLayer::create(_GameScene);
	_GameScene->addChild(setting);
}

void MenuLayer::bmbButtonCallback(cocos2d::Ref* sender)
{
	int boombs = GameData::getInstance()->getBoombs();
	if (boombs > 0) {
		boombs--;
		GameData::getInstance()->setBoombs(boombs);
		GameData::getInstance()->saveBoombs();
		this->refreshUI();
		_GameScene->getFishLayer()->removeFishWithBloomb();
	} else {
		PaymentLayer* payLayer = PaymentLayer::create(_GameScene, PayType(0));
		_GameScene->addChild(payLayer, 10);
	}
}

void MenuLayer::refreshUI()
{
	// �ȼ����� 
	// ��ǰ�ĵȼ�
	int currcertLevel = GameData::getInstance()->getPlayerCurrcertLevel();
	// ��һ�ȼ�
	int nextLevel = currcertLevel + 1;
	int nextLevelNeedExp = GetExpByLevel(nextLevel);
	int playerExp = GameData::getInstance()->getPlayerLevelExp();
	if (playerExp >= nextLevelNeedExp) {
		playerExp -= nextLevelNeedExp;
		currcertLevel += 1;
		GameData::getInstance()->setPlayerLevelExp(playerExp);
		GameData::getInstance()->savePlayerLevelExp();
		GameData::getInstance()->setPlayerCurrcertLevel(currcertLevel);
		GameData::getInstance()->savePlayerCurrcertLevel();
	}
	_levelText->setString(String::createWithFormat("%d", currcertLevel)->_string);
	const float precent = float((float)playerExp / (float)nextLevelNeedExp)*100.0f;
	_levelLoadingBar->setPercent(precent);
	// ÿ�����񲿷�

	// ��������
	int coin = GameData::getInstance()->getPlayerGold();
	_goldText->setString(String::createWithFormat("%d", coin)->_string);

	//// ����
	int light = GameData::getInstance()->getLightLevelExp();
	float percent = (light* 100.0f / 100.0f);
	_lightLoadingBar->setPercent(percent);
	if (percent == 100.0f) {
		_cannon->setType(CannonType::CANNON_TYPE_07);
		_lightLoadingBar->setPercent(0);
		GameData::getInstance()->setLightLevelExp(0);
		GameData::getInstance()->saveLightLevelExp();
	}
	// �߱�ը������
	int boombs = GameData::getInstance()->getBoombs();
	_boombText->setString(String::createWithFormat("%d", boombs)->_string);

}

void MenuLayer::setTouchedEnable(bool enable)
{
	_touchEnable = enable;
}

void MenuLayer::createGoldAt(bool isArray, cocos2d::Vec2 location)
{
	if (!isArray){
		Gold* gold = Gold::create(this, this->convertToWorldSpace(location), Vec2(100, 28));
		addChild(gold);
	}
	else{
		Vec2 goldPos[7] = {
			{ Vec2(320, 180) },{ Vec2(280, 180) },{ Vec2(240, 180) },{ Vec2(200, 180) },
			{ Vec2(280, 140) },{ Vec2(240, 140) },{ Vec2(200, 140) }
		};
		for (int i = 0; i < 7; i++){
			Gold* gold = Gold::create(this, goldPos[i], Vec2(100, 28));
			addChild(gold);
		}
	}
}