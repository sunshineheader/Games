#ifndef __PAYMENT__LAYER__H__H__
#define __PAYMENT__LAYER__H__H__
#include "BaseLayer.h"

enum PayType
{
	PAY_TYPE_00,
	PAY_TYPE_01,
	PAY_TYPE_02,
	PAY_TYPE_03,
};

class PaymentLayer :public BaseLayer
{
public:
	static PaymentLayer* create(GameScene* scene);
	bool init(GameScene* scene);
private:
	void doEvent();
	void doUI();
	void removeEvent();
};

#endif