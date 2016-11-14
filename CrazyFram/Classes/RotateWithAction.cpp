#include "RotateWithAction.h"
#include "GameHelper.h"

RotateWithAction::RotateWithAction()
{
}
RotateWithAction::~RotateWithAction()
{
	CC_SAFE_RELEASE(_innerAction);
}
RotateWithAction* RotateWithAction::create(cocos2d::ActionInterval* action)
{
	RotateWithAction* rotate = new RotateWithAction();
	if (rotate&&rotate->initWithAction(action))
	{
		rotate->autorelease();
		return rotate;
	}
	CC_SAFE_DELETE(rotate);
	return nullptr;
}
void RotateWithAction::startWithTarget(cocos2d::Node *target)
{
	_innerTarget = target;
	cocos2d::Action::startWithTarget(target);
	_innerAction->startWithTarget(target);
}
bool RotateWithAction::initWithAction(cocos2d::ActionInterval* action)
{
	action->retain();
	_innerAction = action;
	return true;
}
bool RotateWithAction::isDone()
{
	return _innerAction->isDone();
}
void RotateWithAction::step(float delta)
{
	cocos2d::Vec2 prevPos = _innerTarget->getPosition();
	_innerAction->step(delta);
	cocos2d::Vec2 currPos = _innerTarget->getPosition();
	float angle = GameHelper::getAngle(prevPos, currPos);
	_innerTarget->setRotation(angle);

}

void RotateWithAction::setInnerAction(cocos2d::ActionInterval* action)
{
	if (_innerAction != action)
	{
		CC_SAFE_RELEASE(_innerAction);
		_innerAction = action;
		CC_SAFE_RETAIN(_innerAction);
	}
}