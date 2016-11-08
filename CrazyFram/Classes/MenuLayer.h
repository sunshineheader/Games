#ifndef __MENU__LAYER__H__H__
#define __MENU__LAYER__H__H__
#include "BaseLayer.h"

class Cannon;
class MenuLayer :public BaseLayer
{
public:
	static MenuLayer* create(GameScene* scene);
	bool init(GameScene* scene);
private:
	void doEvent();
	void doUI();
	void removeEvent();
private:
	void addTouchEvent();
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*) override;
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*) override;
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*) override;
	void removeTouchEvent();
private: // cannon 
	void createCannon();
	void changeCannon();
	bool checkCoin();
	void cannonAimAt(cocos2d::Vec2 location);
	void createBullet(cocos2d::Vec2 position, int type);
	void createLighting(cocos2d::Vec2 position);

private: // callbacks
	void buyButtonCallback(cocos2d::Ref* sender); // π∫¬Ú
	void boxButtonCallback(cocos2d::Ref* sender); // ±¶œ‰
	void addButtonCallback(cocos2d::Ref* sender); // ‘ˆº”
	void subButtonCallback(cocos2d::Ref* sender); // ºı…Ÿ
	void setButtonCallback(cocos2d::Ref* sender); // …Ë÷√
	void bmbButtonCallback(cocos2d::Ref* sender); // ’®µØ
public:
	void refreshUI();
	void setTouchedEnable(bool enable);
private:
	Text* _levelText;
	Text* _goldText;
	Text* _boombText;
	LoadingBar* _levelLoadingBar;
	LoadingBar* _lightLoadingBar;
private:
	Cannon* _cannon;
	bool _touchEnable;

};

#endif
