#ifndef __TASK__OBJECT__H__H__
#define __TASK__OBJECT__H__H__
#include "BaseObject.h"

class MenuLayer;
class Task :public BaseObject
{
public:
	static Task* create(MenuLayer* layer);
private:
	bool init(MenuLayer* layer);
	void initObject();
	void destoryObject();
private:
	MenuLayer*_menuLayer;
	bool _taskHasFinisheed;

};
#endif




