#include "GameScene.h"
#include "GameData.h"
#include "InitLayerHeader.h"
#include "Task.h"
using namespace cocos2d;


Task*Task::create(MenuLayer* layer , TaskData data)
{
	Task* task = new Task();
	if (task && task->init(layer,data))
	{
		task->autorelease();
		return task;
	}
	CC_SAFE_DELETE(task);
	return nullptr;
}

bool Task::init(MenuLayer* layer, TaskData data)
{
	if (!BaseObject::init())
	{
		return false;
	}
	_menuLayer = layer;
	_curTask = data;
	this->_initObject = std::bind(&Task::initObject, this);
	this->_destoryObject = std::bind(&Task::destoryObject, this);
	return true;
}

void Task::initObject()
{
	_taskHasFinisheed = false;
	const std::string RESOURCE_NAME = "Task.csb";
	auto rootNode = CSLoader::createNode(RESOURCE_NAME);
	addChild(rootNode);
	ImageView* image = static_cast<ImageView*>(GameHelper::seekNodeByName(rootNode, "fish_iocn"));
	int icon = _curTask.fishType;
	image->loadTexture(String::createWithFormat("Game/Pic/fish_icon_%d.png", icon)->_string, cocos2d::ui::Widget::TextureResType::PLIST);
	
	// 
    time = ScheduleCountDown::create(120,false);
	time->setPosition(Vec2(50, 10));
	addChild(time);

    num = Text::create();
	num->setPosition(Vec2(50, -10));
	num->setFontSize(18);
	addChild(num);
	num->setString(String::createWithFormat("%d : %2d", _curTask.taskFishNumber, 0)->_string);
	_menuLayer->GetGameScene()->getFishLayer()->setTask(true);
	scheduleUpdate();
}

void Task::destoryObject()
{
	_menuLayer->GetGameScene()->getFishLayer()->setTask(false);
	if (_taskHasFinisheed) {
		int coin = GameData::getInstance()->getPlayerGold();
		coin += _curTask.taskAward;
		GameData::getInstance()->setPlayerGold(coin);
		GameData::getInstance()->savePlayerGold();
		_menuLayer->refreshUI();
	}
}

void Task::update(float dt)
{
	if (time->getCurTime() == 0)
	{
		this->removeFromParentAndCleanup(true);
	}
}

void Task::updateTask()
{
	_curTask.currcertFishNumber = _curTask.currcertFishNumber + 1;
	num->setString(String::createWithFormat("%d : %2d", _curTask.taskFishNumber,  _curTask.currcertFishNumber)->_string);

	if (_curTask.currcertFishNumber >= _curTask.taskFishNumber) {
		_taskHasFinisheed = true;
		this->removeFromParentAndCleanup(true);
	}
}