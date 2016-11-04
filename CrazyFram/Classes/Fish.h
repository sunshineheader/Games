#ifndef __FISH__OBJECT__H__H__
#define __FISH__OBJECT__H__H__
#include "BaseObject.h"

class Fish :public BaseObject
{
public:
	static Fish* create();
private:
	bool init();
	void initObject();
	void destoryObject();
private:
	void move();
	void moveWithDirPath();
	void moveWithAutoPath();
	void moveWithCirclePath();
	void moveWithBezierPath();
};

#endif