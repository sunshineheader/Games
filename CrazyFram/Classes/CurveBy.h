#ifndef __CURVEBY__H__H__
#define __CURVEBY__H__H__
#include "cocos2d.h"

typedef struct _ccQuadBezierConfig {
	cocos2d::Vec2 endPosition;
	cocos2d::Vec2 controlPoint;
} ccQuadBezierConfig;

class CurveBy :public cocos2d::BezierBy
{
public:
	CurveBy();
	static CurveBy* create(float duration, const ccQuadBezierConfig& config);
	bool initWithDuration(float duration, const ccQuadBezierConfig& config);
	virtual void update(float delta);
private:
	ccQuadBezierConfig _config;
};

#endif




