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
	FISH_TYPE_09,
	FISH_TYPE_10,// red
	FISH_TYPE_11 // prop
};

// 鱼的信息
typedef struct
{
	FishType fishType;            // 鱼的类型
	int      fishGold;            // 击杀鱼所得到的金币
	int	     fishSpeed;           // 鱼的游动速度
	float    fishRate;            // 鱼的出现几率
	int      fishExp;             // 击杀鱼所得到的经验
	int      fishLight;           // 击杀鱼所得的激光经验
	int      fishSwingFrames;     // 鱼的游动动画帧数
	int      fishDeadFrames;      // 鱼的死亡动画帧数
}FishInfo;

enum FishStatus
{
	FISH_MOVE,
	FISH_DEAD
};

// 移动路径结构
typedef struct 
{
	cocos2d::Vec2 startPos; // 起点
	cocos2d::Vec2 endedPos; // 终点
}DirPath;

typedef struct 
{
	cocos2d::Vec2 circleCenter; // 圆心
	float circleRadius;			// 半径
	float circleAngle;			// 转过的角度
}CirclePath;

typedef struct 
{
	cocos2d::Vec2 startPosition;
	cocos2d::Vec2 controlPoint1;
	cocos2d::Vec2 controlPoint2;
	cocos2d::Vec2 ebdedPosition;
	float time;
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
	void moveWithBezierPath();
	void moveWithBezierPathByPathType(int type);
private:
	void moveWithStraight(bool direction, cocos2d::Vec2 startPos, cocos2d::Vec2 endedPos);
	void moveWithBezier(bool direction, cocos2d::Vec2 startPos, cocos2d::Vec2  controlPoint1, cocos2d::Vec2  controlPoint2, cocos2d::Vec2 endedPos, float time);
public: // set get
	int getType();
	int getExpByType();
	int getGoldByType();
public:
	bool isCatched(){ return _isCatched; };
	void setCatched(bool mcatch){ _isCatched = mcatch; };
	cocos2d::Rect getCollisionRect();
	//void moveWithBezier(cocos2d::Vec2 form, cocos2d::Vec2 to,float time,bool direction);
private:
	FishLayer*_fishLayer;
	cocos2d::Sprite*_fishSprite;
	bool _isCatched;
private:
	static DirPath _DirPath[10];
	static BezierPath _BezierPath[12];
	FishInfo _fishInfo;
private:
	static char* FISH_RESOURCES;

};

#endif