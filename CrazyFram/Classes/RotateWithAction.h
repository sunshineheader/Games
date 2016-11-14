#ifndef __ROTATION_WITH_ACTIONS__
#define __ROTATION_WITH_ACTIONS__

#include "cocos2d.h"

class RotateWithAction :public cocos2d::ActionInterval
{
public:
	RotateWithAction();
	~RotateWithAction();
	static RotateWithAction* create(cocos2d::ActionInterval* action);
	virtual void startWithTarget(cocos2d::Node *target)override;
	bool initWithAction(cocos2d::ActionInterval* action);
	bool isDone();
	void step(float delta);
protected: 
	void setInnerAction(cocos2d::ActionInterval* action);
	cocos2d::Node *_innerTarget;
	cocos2d::ActionInterval* _innerAction;
};
#endif



