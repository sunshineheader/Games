#include "CurveBy.h"


static inline float beziertacurveby(float a, float b, float d, float t)
{
	return (powf(1 - t, 2) * a +
		2.0f*t*(1 - t)*b +
		powf(t, 2)*d);
}


CurveBy::CurveBy()
{
}
CurveBy* CurveBy::create(float duration, const ccQuadBezierConfig& config)
{
	CurveBy *curveBy = new (std::nothrow) CurveBy();
	curveBy->initWithDuration(duration, config);
	curveBy->autorelease();
	return curveBy;
}
bool CurveBy::initWithDuration(float duration, const ccQuadBezierConfig& config)
{
	if (!cocos2d::ActionInterval::initWithDuration(duration)) 
	{
		return false;
	}
	_config = config;
	return true;
}

void CurveBy::update(float delta)
{
	// 1
	if (_target) {
		// 2
		float xa = 0;
		float xb = _config.controlPoint.x;
		float xc = _config.endPosition.x;

		float ya = 0;
		float yb = _config.controlPoint.y;
		float yc = _config.endPosition.y;

		float x = beziertacurveby(xa, xb, xc, delta);
		float y = beziertacurveby(ya, yb, yc, delta);

#if CC_ENABLE_STACKABLE_ACTIONS
		// 3    
		cocos2d::Vec2 currentPos = _target->getPosition();
		cocos2d::Vec2 diff = currentPos - _previousPosition;
		_startPosition = _startPosition + diff;

		cocos2d::Vec2 newPos = _startPosition + cocos2d::Vec2(x, y);
		_target->setPosition(newPos);

		_previousPosition = newPos;

		//// 4
		//if (0 != time) {
		//	cocos2d::Vec2 vector = currentPos - newPos;
		//	float radians = vector.getAngle();
		//	float degrees = CC_RADIANS_TO_DEGREES(-1 * radians);
		//	_target->setRotation(degrees - 180);
		//}

#else
		_target->setPosition(_startPosition + Vec2(x, y));
#endif // !CC_ENABLE_STACKABLE_ACTIONS

	}
}