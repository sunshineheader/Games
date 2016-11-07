#ifndef __GAME__HELPER__H__H__
#define __GAME__HELPER__H__H__
#include "cocos2d.h"

class GameHelper {

public:
	GameHelper();
	~GameHelper();
	static cocos2d::Node* seekNodeByName(cocos2d::Node* root, const std::string& name);
	static float getAngle(cocos2d::Vec2 stratPos, cocos2d::Vec2 endedPos);

private:


};

#endif // !__GAME__HELPER__H__H__