#include "BaseObject.h"
using namespace cocos2d;

BaseObject::BaseObject()
	:_initObject(nullptr)
	, _destoryObject(nullptr)
{}

BaseObject::~BaseObject()
{}

void BaseObject::onEnter()
{
	Node::onEnter();
	if (_initObject)	_initObject();
}
void BaseObject::onExit()
{
	Node::onExit();
	if (_destoryObject)	_destoryObject();
}