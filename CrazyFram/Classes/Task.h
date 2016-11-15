#ifndef __TASK__OBJECT__H__H__
#define __TASK__OBJECT__H__H__
#include "BaseObject.h"
#include "Fish.h"
#include "CutDown.h"

typedef struct {
	FishType fishType;
	int taskFishNumber;
	int currcertFishNumber;
	float taskAward;
}TaskData;

class MenuLayer;
class Task :public BaseObject
{
public:
	static Task* create(MenuLayer* layer, TaskData data);
	void updateTask();
private:
	bool init(MenuLayer* layer, TaskData data);
	void initObject();
	void destoryObject();
	void update(float dt);
private:
	MenuLayer*_menuLayer;
	bool _taskHasFinisheed;

	TaskData _curTask;
	cocos2d::ui::Text* num;
	ScheduleCountDown* time;


};
#endif




