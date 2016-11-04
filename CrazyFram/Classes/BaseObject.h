#ifndef __BASE__OBJECT__H__H__
#define __BASE__OBJECT__H__H__
#include "cocos2d.h"

class BaseObject :public cocos2d::Node
{
protected:
	BaseObject();
	~BaseObject();
protected:
	virtual void onEnter()override;
	virtual void onExit()override;
protected:
	std::function<void()>_initObject;
	std::function<void()>_destoryObject;
};

#endif