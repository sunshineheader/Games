#ifndef __PAYMENT__LAYER__H__H__
#define __PAYMENT__LAYER__H__H__
#include "BaseLayer.h"

enum PayType
{
	PAY_TYPE_00,// 高爆炸弹
	PAY_TYPE_01,// 金币充值
	PAY_TYPE_02,// 每日任务
	PAY_TYPE_03,// 道具大礼包
};

class PaymentLayer :public BaseLayer
{
public:
	static PaymentLayer* create(GameScene* scene,PayType type);
	bool init(GameScene* scene, PayType type);
	void refreshUI();
private:
	void doEvent();
	void doUI();
	void removeEvent();
private:
	PayType _type;

};

#endif