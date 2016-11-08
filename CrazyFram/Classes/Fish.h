#ifndef __FISH__OBJECT__H__H__
#define __FISH__OBJECT__H__H__
#include "BaseObject.h"

enum FishType
{
	FISH_TYPE_00,
	FISH_TYPE_01,
	FISH_TYPE_02,
	FISH_TYPE_03,
	FISH_TYPE_04,
	FISH_TYPE_05,
	FISH_TYPE_06,
	FISH_TYPE_07,
	FISH_TYPE_08,
	FISH_TYPE_09
};

// �����Ϣ
typedef struct
{
	FishType fishType;            // �������
	int      fishGold;            // ��ɱ�����õ��Ľ��
	int	     fishSpeed;           // ����ζ��ٶ�
	float    fishRate;            // ��ĳ��ּ���
	int      fishExp;             // ��ɱ�����õ��ľ���
	int      fishSwingFrames;     // ����ζ�����֡��
	int      fishDeadFrames;      // �����������֡��
}FishInfo;

enum FishStatus
{
	FISH_MOVE,
	FISH_DEAD
};

// �ƶ�·���ṹ
typedef struct 
{
	cocos2d::Vec2 startPos; // ���
	cocos2d::Vec2 endedPos; // �յ�
}DirPath;

typedef struct 
{
	cocos2d::Vec2 circleCenter; // Բ��
	float circleRadius;			// �뾶
	float circleAngle;			// ת���ĽǶ�
}CirclePath;

typedef struct 
{
}BezierPath;

class FishLayer;
class Fish :public BaseObject
{
public:
	static Fish* create(FishLayer* layer, FishInfo info);
private:
	bool init(FishLayer* layer, FishInfo info);
	void initObject();
	void destoryObject();
	void resetMe();
	void deleteMe();
public:
	void playSwingAnimation();
	void playDeadAnimation();
public:
	void move();
	void moveWithDirPath();
	void moveWithAutoPath();
	void moveWithCirclePath();
	void moveWithBezierPath();
private:
	void moveWithStraight(cocos2d::Vec2 startPos, cocos2d::Vec2 endedPos);
	void moveWithCircle(float duraction, cocos2d::Vec2 circleCenter, float radius,float angle);
	void moveWithBezier();

public: // set get
	int getExpByType();
	int getGoldByType();
public:
	cocos2d::Sprite*getFishSprite();
	cocos2d::Rect getCollisionRect();
private: //////////// TESTING MENGTHON
	//void dtawFishRect();
private:
	FishLayer*_fishLayer;
	cocos2d::Sprite*_fishSprite;
private:
	static DirPath _DirPath[20];
	FishInfo _fishInfo;
private:
	static char* FISH_RESOURCES;

};

#endif