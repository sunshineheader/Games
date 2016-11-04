#ifndef __BACKGROUND__LAYER__H__H__
#define __BACKGROUND__LAYER__H__H__
#include "BaseLayer.h"

class BackgroundLayer :public BaseLayer
{
public:
	static BackgroundLayer* create();
private:
	bool init();
	void doEvent();
	void doUI();
	void removeEvent();
};

#endif