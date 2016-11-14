#ifndef __PAYMENT__LAYER__H__H__
#define __PAYMENT__LAYER__H__H__
#include "BaseLayer.h"

enum PayType
{
	PAY_TYPE_00,// �߱�ը��
	PAY_TYPE_01,// ��ҳ�ֵ
	PAY_TYPE_02,// ÿ������
	PAY_TYPE_03,// ���ߴ����
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