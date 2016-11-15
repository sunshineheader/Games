#ifndef __SCHEDULE_COUNT_DOWN__H__H__
#define __SCHEDULE_COUNT_DOWN__H__H__
#include "BaseObject.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

class ScheduleCountDown : public BaseObject
{
public:
	static ScheduleCountDown* create(int perimeter = 60, bool loop = true);
	bool init(int perimeter, bool loop);
	void schedulePerSecond(float delta);
	std::string convertSecondToMin(int second);

public:
	void setLoop(bool loop){ _loop = loop; };
	bool getLoop(){ return _loop; };
	inline int  getCurTime(){ return _curTime; };
private:
	int _maxTime;
	int _curTime;
	bool _loop;
	cocos2d::ui::Text* _countDown;
};

#endif



