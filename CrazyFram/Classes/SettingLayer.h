#ifndef __SETTING__LAYER__H__H__
#define __SETTING__LAYER__H__H__
#include "BaseLayer.h"

class SettingLayer :public BaseLayer
{
public:
	static SettingLayer* create(GameScene* scene);
	bool init(GameScene* scene);
private:
	void doEvent();
	void doUI();
	void removeEvent();
};

#endif