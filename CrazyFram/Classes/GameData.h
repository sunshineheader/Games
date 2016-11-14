#ifndef _GAME__DATA__H__H__
#define _GAME__DATA__H__H__
#include "cocos2d.h"

class GameData {

public:
	GameData();
	~GameData();
	static GameData* getInstance();
	static void destoryInstance();
public:

	bool getMusicStatus();
	inline void setMusicStatus(bool status){ _bgMusic = status; };

	bool getEffectStatus();
	inline void setEffectStatus(bool status){ _effectMusic = status; };

	int getPlayerGold();
	inline void setPlayerGold(int gold){ _golds = gold; };

	int getPlayerCurrcertLevel();
	inline void setPlayerCurrcertLevel(int level){ _level = level; };

	int getPlayerLevelExp();
	inline void setPlayerLevelExp(int exp){ _levelExp = exp; };

	int getLightLevelExp();
	inline void setLightLevelExp(int exp){ _lightExp = exp; };

	int getCannonType();
	inline void setCannonType(int type){ _cannonType = type; };

	int getBoombs();
	inline void setBoombs(int num){ _boombs = num; };
public:
	void saveMusicStatus();
	void saveEffectStatus();

	void savePlayerGold();
	void savePlayerLevelExp();
	void saveLightLevelExp();
	void savePlayerCurrcertLevel();
	void saveCannonType();
	void saveBoombs();
private:
	static GameData* _instance;
	bool _bgMusic;
	bool _effectMusic;
	int _golds;
	int _level;
	int _levelExp;
	int _lightExp;
	int _cannonType;
	int _boombs;




};

#endif // !__GAME__HELPER__H__H__