#ifndef __LOADINGLAYER__LAYER__H__H__
#define __LOADINGLAYER__LAYER__H__H__
#include "BaseLayer.h"

class LoadingLayer :public BaseLayer
{
public:
	static cocos2d::Scene* createScene();
private:
	static LoadingLayer* create();
	bool init();
	void doEvent();
	void doUI();
	void removeEvent();
	void initGameSetting();
	// 实现异步加载
	void loadGameResourcesAsynchronous(cocos2d::Texture2D* texture);
private:
	int _totalFiles;
	int _currcertFile;
};

#endif
