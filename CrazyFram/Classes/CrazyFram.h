#ifndef __CRAZYFRAM__H__H__
#define __CRAZYFRAM__H__H__

#include <string>
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;

// 中文的转化
static std::string GetChineseWord(const std::string wordId)
{
	ValueVector txt_vec = FileUtils::getInstance()->getValueVectorFromFile("ChineseWords.plist");
	auto txt_map = txt_vec.at(0).asValueMap();
	std::string ret = txt_map.at(wordId).asString();
	return ret;
}

// 通过等级获取所需要的经验
static int GetExpByLevel(int level)
{
	if (level > 40)
	{
		return 0;
	}
	return int((std::pow((level - 1), 3) + 60) / (5 * (level - 1) * 2 + 60) * 100);
}

static float GetFishHitRate(int netType, int fishGolds)
{
	// 命中率={炮台*（1-0.1）}/鱼的分值
	return float(((netType + 1) * (1 - 0.1)) / fishGolds);
}

#endif//__CONSTANTS__H__H__



