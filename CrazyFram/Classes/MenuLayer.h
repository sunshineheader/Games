#ifndef __MENU__LAYER__H__H__
#define __MENU__LAYER__H__H__
#include "BaseLayer.h"

class MenuLayer :public BaseLayer
{
public:
	static MenuLayer* create();
	bool init();
private:
	void doEvent();
	void doUI();
	void removeEvent();
};

#endif
