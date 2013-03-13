//
//  Map.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/30.
//
//

#ifndef __VOXCHRONICLE__Map__
#define __VOXCHRONICLE__Map__

#include <iostream>
#include "cocos2d.h"
#include "Level.h"
#include "LuaObject.h"
#include "MusicSet.h"
#include "CharacterManager.h"
#include "EnemyManager.h"
#include "Skin.h"
#include "Character.h"

using namespace std;
using namespace cocos2d;

class Map :public CCObject {
 private:
  int _endLevel;
  int _initialLevel;
  int _maxLevel;
  string _identifier;
  vector<string>* _nextMaps;
  string _name;
  string _backgroundImageName;
  string _ending;
  CCSprite* _background;
  LuaObject* _lua;
  list< pair<string, int> >* _fixedEnemyTable; // 固定モンスターテーブル
  MusicSet* _wayMusic;
  MusicSet* _bossMusic;
  Skin* _skin;
  void loadSkillTable(Character* character);
  CCDictionary* _skillCache;
 public:
  Map(const char* mapName);
  ~Map();
  Level* createLevel(int level, CharacterManager* manager);
  Level* createInitialLevel(CharacterManager* manager);
  int getMaxLevel();
  int getInitialLevel();
  string getName();
  string getIdentifier();
  string getEndingName();
  CCSprite* getBackground();
  CCArray* getFixedEnemies(int preExp, int currentExp);
  CCArray* getNextMaps();
  bool isBossStage();
  MusicSet* getWayMusic();
  MusicSet* getBossMusic();
  MusicSet* getCurrentMusic(Level* level);
  void performOnLevel(int level, CharacterManager* characterManager, EnemyManager* enemyManager);
  Skin* getSkin();
};

#endif /* defined(__VOXCHRONICLE__Map__) */
