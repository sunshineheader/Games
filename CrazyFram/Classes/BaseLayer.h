#ifndef __BASE__LAYER__H__H__
#define __BASE__LAYER__H__H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

class GameScene;
class BaseLayer :public cocos2d::Layer 
{
protected:
	BaseLayer();
	~BaseLayer();
	bool init();
	void init(GameScene* scene);
	virtual void onEnter()override;
	virtual void onExit()override;

protected:
	std::function<void()>_doEvent;
	std::function<void()>_doUI;
	std::function<void()>_removeEvent;

protected:
	std::string RESOURCE_NAME;
	GameScene*_GameScene;

};
#endif



