#ifndef __FISH__LAYER__H__H__
#define __FISH__LAYER__H__H__
#include "BaseLayer.h"

class FishLayer :public BaseLayer
{
public:
	static FishLayer* create();
	bool init();
private:
	void doEvent();
	void doUI();
	void removeEvent();
};

#endif
