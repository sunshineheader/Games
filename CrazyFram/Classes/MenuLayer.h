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
	void createCannon();	// 创建的炮塔
	bool checkCoin(); // 检查金币
	void changeCannon();// 改变炮塔
	void cannonAimAt(cocos2d::Vec2 location);
	void createBullet(cocos2d::Vec2 position, int type);
	void createLighting(cocos2d::Vec2 position);
private: // callbacks
	void buyButtonCallback(cocos2d::Ref* sender); // 购买
	void boxButtonCallback(cocos2d::Ref* sender); // 宝箱
	void addButtonCallback(cocos2d::Ref* sender); // 增加
	void subButtonCallback(cocos2d::Ref* sender); // 减少
	void setButtonCallback(cocos2d::Ref* sender); // 设置
	void bmbButtonCallback(cocos2d::Ref* sender); // 炸弹

public:
	void refreshUI();
	void setTouchedEnable(bool enable);
	void createGoldAt(bool isArray,cocos2d::Vec2 location = cocos2d::Vec2::ZERO);
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
