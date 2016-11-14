#ifndef __PAYNODESCEOND__H__H__
#define __PAYNODESCEOND__H__H__
#include "BaseObject.h"

class PaymentLayer;
class PayNodeSceond :public BaseObject  {

public:
	static PayNodeSceond* create(PaymentLayer* layer, int type);
	bool init (PaymentLayer* layer, int type);

	void initObject();
	void destoryObject();
private:
	void closeBtnCallBack(cocos2d::Ref* ref );
	void buyBtnCallBack(cocos2d::Ref* ref);
private:
	PaymentLayer* _layer;
	int _type;
	int _prop1Num;
	int _prop2Num;

	bool _isBuy;
};


#endif
