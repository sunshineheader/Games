#include "CutDown.h"

ScheduleCountDown*ScheduleCountDown::create(int perimeter, bool loop)
{
	ScheduleCountDown* countDown = new (std::nothrow) ScheduleCountDown();
	if (countDown && countDown->init(perimeter, loop))
	{
		countDown->autorelease();
		return countDown;
	}
	CC_SAFE_DELETE(countDown);
	return nullptr;
}



bool ScheduleCountDown::init(int perimeter, bool loop)
{
	if (!Node::init()) {

		return false;
	}

	_maxTime = perimeter;
	_curTime = _maxTime;
	_loop = loop;

	std::string count = convertSecondToMin(_curTime);
	_countDown = ui::Text::create(count, "", 18);
	setContentSize(_countDown->getContentSize());
	addChild(_countDown);

	this->schedule(schedule_selector(ScheduleCountDown::schedulePerSecond), 1.0f);
	return true;
}
void ScheduleCountDown::schedulePerSecond(float delta)
{
	_curTime--;
	if (_curTime <= 0){
		if (this->getLoop()){
			_curTime = _maxTime;
		}
		else{
			this->unschedule(schedule_selector(ScheduleCountDown::schedulePerSecond));
		}

	}
	std::string count = convertSecondToMin(_curTime);
	_countDown->setString(count);
}

std::string ScheduleCountDown::convertSecondToMin(int second)
{
	if (second > 60)
	{
		int min = second / 60;
		int remainder = second % 60;
		return cocos2d::String::createWithFormat("%02d : %02d", min, remainder)->_string;
	}
	return cocos2d::String::createWithFormat("%02d : %02d", 0 ,second)->_string;
}

