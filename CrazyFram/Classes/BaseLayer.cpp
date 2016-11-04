#include "GameScene.h"
#include "BaseLayer.h"

BaseLayer::BaseLayer()
	:RESOURCE_NAME("")
	, _GameScene(nullptr)
	, _doEvent(nullptr)
	, _doUI(nullptr)
	, _removeEvent(nullptr)
{}

BaseLayer::~BaseLayer()
{}

bool BaseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}
void BaseLayer::init(GameScene* scene)
{
	if (!this->init())
	{
		return;
	}
	_GameScene = scene;
}

void BaseLayer::onEnter()
{
	Layer::onEnter();
	if (_doEvent)	_doEvent();
	if (_doUI)		_doUI();

}
void BaseLayer::onExit()
{
	Layer::onExit();
	if (_removeEvent)  _removeEvent();
}