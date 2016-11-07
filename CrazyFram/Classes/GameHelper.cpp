#include "GameHelper.h"
using namespace cocos2d;

GameHelper::GameHelper()
{}

GameHelper::~GameHelper()
{}

Node* GameHelper::seekNodeByName(Node* root, const std::string& name) {
	if (!root) {
		return nullptr;
	}
	if (root->getName() == name) {
		return root;
	}
	const auto& arrayRootChildren = root->getChildren();
	for (auto& subWidget : arrayRootChildren)
	{
		Node* child = dynamic_cast<Node*>(subWidget);
		if (child)
		{
			Node* res = seekNodeByName(child, name);
			if (res != nullptr)
			{
				return res;
			}
		}
	}
	return nullptr;
}

float GameHelper::getAngle(cocos2d::Vec2 stratPos, cocos2d::Vec2 endedPos)
{
	float distanceY = endedPos.y - stratPos.y;
	float distanceX = endedPos.x - stratPos.x;
	float radian = Vec2(distanceY, distanceX).getAngle();
	return CC_RADIANS_TO_DEGREES(radian);
}
