#ifndef __GOLD__H__H__
#define __GOLD__H__H__

#include "BaseObject.h"

class FishLayer;
class Gold :public BaseObject
{
public:
	static Gold* create(FishLayer* layer);
private:
	bool init(FishLayer* layer);
	void initObject();
	void destoryObject();

private:
	FishLayer* _fishLayer;
};

#endif


