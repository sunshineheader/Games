#include "MenuLayer.h"
#include "Task.h"
using namespace cocos2d;

TaskData Task::_taskData[6] =
{
	{ FishType(0), 10, 0, 200 },
	{ FishType(2), 5, 0,  200 },
	{ FishType(4), 5, 0,  200 },
	{ FishType(5), 5, 0,  300 },
	{ FishType(7), 3, 0,  300 },
	{ FishType(9), 3, 0,  300 }
};

Task*Task::create(MenuLayer* layer)
{
	Task* task = new Task();
	if (task && task->init(layer))
	{
		task->autorelease();
		return task;
	}
	CC_SAFE_DELETE(task);
	return nullptr;
}

bool Task::init(MenuLayer* layer)
{
	if (!BaseObject::init())
	{
		return false;
	}
	_menuLayer = layer;
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



}

void Task::destoryObject()
{
	if (_taskHasFinisheed) {
		_menuLayer->refreshUI();
	}
}