#ifndef __PAYNODE__FIRST__H__H__
#define __PAYNODE__FIRST__H__H__
#include "BaseObject.h"

class PaymentLayer;
class PayNodeFirst :public BaseObject  {

public:
	static PayNodeFirst* create(PaymentLayer* layer, int type);
	bool init (PaymentLayer* layer, int type);

	void initObject();
	void destoryObject();
private:
	void closeBtnCallBack(cocos2d::Ref* ref );
	void buyBtnCallBack(cocos2d::Ref* ref);
private:
	PaymentLayer* _layer;
	int _type;
	int _propNum;
	bool _isBuy;
};



#endif