//
//  SaveData.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/2.
//
//

#ifndef __VOXCHRONICLE__SaveData__
#define __VOXCHRONICLE__SaveData__

#include <iostream>
#include <list>
#include "cocos2d.h"
#include "Map.h"
#include "Enemy.h"

using namespace std;
using namespace cocos2d;

/**
 セーブデータクラスです
 到達状況やスコアや、その他諸々がここに格納されます
 save/loadはCCUserDefaultに任せます。
 */

typedef enum {
  SaveDataCountKeyDead,
  SaveDataCountKeyTurn,
  SaveDataCountKeyDefeat,
  SaveDataCountKeyMPMiss,
  SaveDataCountKeyBoot,
  SaveDataCountKeyHitDamage,
  SaveDataCountKeyAttackDamage,
  SaveDataCountKeyDictionaryCount,
  SaveDataCountKeyClear, // クリア回数
  SaveDataCountKeyNum
} SaveDataCountKey;

typedef struct {
  SaveDataCountKey key;
  int count;
  string identifier;
} AchievementInfo;

class SaveData :public CCObject {
 private:
  static SaveData* _shared;
  bool _fullvoice;
  bool _isInitialBoot;
  CCDictionary* _countDictionary;
  CCArray* _achievements;
  shared_ptr<CCLuaValueArray> _enemyDictionary;
  
  list<AchievementInfo>* _achievementInfos;
  
  void checkUnlockAchievement(SaveDataCountKey key, int value);
  void onFinishAchievementReporting(const char* identifier, bool error);
 public:
  static SaveData* sharedData();
  SaveData();
  virtual ~SaveData();
  void save();
  void load();
  int getDefeatedCount(const char* enemyIdentifier);
  void addDefeatedCountForEnemy(const char* enemyIdentifier);
  bool isClearedMap(const char* mapIdentifier);
  void setClearedForMap(const char* mapIdentifier);
  void setCountFor(SaveDataCountKey key, int value);
  void addCountFor(SaveDataCountKey key);
  void addCountFor(SaveDataCountKey key, int value);
  int getScore(const char* mapIdentifier);
  bool updateScore(const char* mapIdentifier, int turn);
  int getCountFor(SaveDataCountKey key);
  bool isUnlockAchievement(const char* identifier);
  void unlockAchievement(const char* identifier);
  void setUnlockedAchievement(const char* identifier);
  int getAllEnemyDictionaryCount();
  bool isFullVoice();
  void setFullVoice(bool b);
  bool isInitialBoot();
  void setInitialBoot(bool f);
};

#endif /* defined(__VOXCHRONICLE__SaveData__) */
