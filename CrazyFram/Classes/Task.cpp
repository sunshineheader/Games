#include "MenuLayer.h"
#include "Task.h"
using namespace cocos2d;

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

}

void Task::destoryObject()
{
	if (_taskHasFinisheed)
	{
		_menuLayer->refreshUI();
	}
}