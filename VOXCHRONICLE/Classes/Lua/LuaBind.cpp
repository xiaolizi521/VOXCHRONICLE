//
//  LuaBind.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/6.
//
//

#include "LuaBind.h"
#include "LuaCocos2d.h"
#include "Skill.h"
#include "Enemy.h"
#include "CharacterManager.h"
#include "EnemyManager.h"
#include "EnemySkill.h"
#include "MusicSet.h"
#include "MessageManager.h"
#include "StatusLayer.h"
#include "Controller.h"

static void tolua_reg_types (lua_State* tolua_S) {
  tolua_usertype(tolua_S, "Skill");
  tolua_usertype(tolua_S, "Enemy");
  tolua_usertype(tolua_S, "CharacterManager");
  tolua_usertype(tolua_S, "EnemyManager");
  tolua_usertype(tolua_S, "EnemySkill");
  tolua_usertype(tolua_S, "MessageManager");
}

// Skill
#pragma mark Skill
static int tolua_VC_Skill_getPower(lua_State* tolua_S) {
  Skill* self = (Skill*)  tolua_tousertype(tolua_S, 1, 0);
  CharacterManager* manager = (CharacterManager*)tolua_tousertype(tolua_S, 2, 0);
  int power = self->getPower(manager);
  lua_pushnumber(tolua_S, power);
  return 1;
}

// Enemy
#pragma mark Enemy

static int tolua_VC_Enemy_getRow(lua_State* tolua_S) {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S, 1, 0);
  float tolua_ret = (float)  self->getRow();
  tolua_pushnumber(tolua_S, (float)tolua_ret);
  return 1;
}

static int tolua_VC_Enemy_moveRow(lua_State* tolua_S) {
  Enemy* self = (Enemy*)tolua_tousertype(tolua_S, 1, 0);
  float row = (float)tolua_tonumber(tolua_S, 2, 0);
  self->moveRow(row);
  return 0;
}

static int tolua_VC_Enemy_setRow(lua_State* tolua_S) {
  Enemy* self = (Enemy*)tolua_tousertype(tolua_S, 1, 0);
  float row = (float)tolua_tonumber(tolua_S, 2, 0);
  self->setRow(row);
  return 0;
}

static int tolua_VC_Enemy_getCol(lua_State* tolua_S) {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S, 1, 0);
  float tolua_ret = (float)  self->getCol();
  tolua_pushnumber(tolua_S, (int)tolua_ret);
  return 1;
}

static int tolua_VC_Enemy_getRegister(lua_State* tolua_S) {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S, 1, 0);
  string key = (string)tolua_tostring(tolua_S, 2, 0);
  int defaultValue = (int)tolua_tonumber(tolua_S, 3, 0);
  float tolua_ret = (int)self->getRegister(key.c_str(), defaultValue);
  tolua_pushnumber(tolua_S, (int)tolua_ret);
  return 1;
}

static int tolua_VC_Enemy_setRegister(lua_State* tolua_S) {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S, 1, 0);
  string key = (string)tolua_tostring(tolua_S, 2, 0);
  int value = (int)tolua_tonumber(tolua_S, 3, 0);
  self->setRegister(key.c_str(), value);
  return 0;
}

static int tolua_VC_Enemy_hasRegister(lua_State* tolua_S) {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S, 1, 0);
  string key = (string)tolua_tostring(tolua_S, 2, 0);
  bool tolua_ret = (bool)self->hasRegister(key.c_str());
  tolua_pushnumber(tolua_S, (bool)tolua_ret);
  return 1;
}

static int tolua_VC_Enemy_setAnimationClip(lua_State* tolua_S) {
  Enemy* self = (Enemy*)tolua_tousertype(tolua_S, 1, 0);
  string clipName = (string)tolua_tostring(tolua_S, 2, 0);
  int frames = (int)tolua_tonumber(tolua_S, 3, 0);
  bool hasFrame = (bool)tolua_toboolean(tolua_S, 4, 0);
  bool tolua_ret = (bool)self->setAnimationClip(clipName.c_str(), frames, hasFrame);
  tolua_pushnumber(tolua_S, (bool)tolua_ret);
  return 1;
}

static int tolua_VC_Enemy_setDefaultAnimationClip(lua_State* tolua_S) {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S, 1, 0);
  bool tolua_ret = (bool)self->setDefaultAnimationClip();
  tolua_pushnumber(tolua_S, (bool)tolua_ret);
  return 1;
}

static int tolua_VC_Enemy_getName(lua_State* tolua_S) {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S, 1, 0);
  const char* name = self->getName().c_str();
  tolua_pushstring(tolua_S, name);
  return 1;
}

static int tolua_VC_Enemy_getHP(lua_State* tolua_S) {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S, 1, 0);
  int hp = self->getHP();
  tolua_pushnumber(tolua_S, hp);
  return 1;
}

// CharacterManager
#pragma mark CharacterManager

static int tolua_VC_CharacterManager_setShield(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  bool shield = (bool)tolua_toboolean(tolua_S, 2, 0);
  self->setShield(shield);
  return 0;
}

static int tolua_VC_CharacterManager_changeCharacter(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  self->changeCharacter();
  return 0;
}

static int tolua_VC_CharacterManager_addTension(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int tension = (int)tolua_tonumber(tolua_S, 2, 0);
  self->addTension(tension);
  return 0;
}

static int tolua_VC_CharacterManager_getTension(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int tension = self->getTension();
  tolua_pushnumber(tolua_S, tension);
  return 1;
}

static int tolua_VC_CharacterManager_getLevel(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int level = (int)self->getLevel();
  tolua_pushnumber(tolua_S, (int)level);
  return 1;
}

static int tolua_VC_CharacterManager_setLevel(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int level = (int)tolua_tonumber(tolua_S, 2, 0);
  self->setLevel(level);
  return 0;
}

static int tolua_VC_CharacterManager_addHP(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int hp = (int)tolua_tonumber(tolua_S, 2, 0);
  int newHP = self->addHP(hp);
  tolua_pushnumber(tolua_S, newHP);
  return 1;
}

static int tolua_VC_CharacterManager_addMP(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int mp = (int)tolua_tonumber(tolua_S, 2, 0);
  int newMP = self->addMP(mp);
  tolua_pushnumber(tolua_S, newMP);
  return 1;
}

static int tolua_VC_CharacterManager_getDrumLevel(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int newHP = self->getDrumLevel();
  tolua_pushnumber(tolua_S, newHP);
  return 1;
}

static int tolua_VC_CharacterManager_setDrumLevel(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int level = (int)tolua_tonumber(tolua_S, 2, 0);
  self->setDrumLevel(level);
  return 0;
}

static int tolua_VC_CharacterManager_damage(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int damage = (int)tolua_tonumber(tolua_S, 2, 0);
  DamageType damageType = (DamageType)self->damage(damage);
  tolua_pushnumber(tolua_S, (int)damageType);
  return 1;
}

static int tolua_VC_CharacterManager_getHP(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int hp = self->getHP();
  tolua_pushnumber(tolua_S, hp);
  return 1;
}

static int tolua_VC_CharacterManager_getMP(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int mp = self->getMP();
  tolua_pushnumber(tolua_S, mp);
  return 1;
}

static int tolua_VC_CharacterManager_getMaxHP(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int maxhp = self->getMaxHP();
  tolua_pushnumber(tolua_S, maxhp);
  return 1;
}

static int tolua_VC_CharacterManager_getMaxMP(lua_State* tolua_S) {
  CharacterManager* self = (CharacterManager*)tolua_tousertype(tolua_S, 1, 0);
  int maxmp = self->getMaxMP();
  tolua_pushnumber(tolua_S, maxmp);
  return 1;
}

// EnemyManager
#pragma mark EnemyManager

static int tolua_VC_EnemyManager_nextTurn(lua_State* tolua_S) {
  EnemyManager* self = (EnemyManager*)tolua_tousertype(tolua_S, 1, 0);
  CharacterManager* characterManager = (CharacterManager*)tolua_tousertype(tolua_S, 2, 0);
  self->nextTurn(characterManager);
  return 0;
}

static int tolua_VC_EnemyManager_popEnemyAt(lua_State* tolua_S) {
  EnemyManager* self = (EnemyManager*)tolua_tousertype(tolua_S, 1, 0);
  string enemyName = (string)tolua_tostring(tolua_S, 2, 0);
  int row = (int)tolua_tonumber(tolua_S, 3, 0);
  int col = (int)tolua_tonumber(tolua_S, 4, 0);
  Enemy* enemy = self->popEnemyAt(enemyName, row, col);
  tolua_pushusertype(tolua_S, (void*)enemy, "Enemy");
  //tolua_register_gc(tolua_S, lua_gettop(tolua_S));
  return 1;
}

static int tolua_VC_EnemyManager_getBoss(lua_State* tolua_S) {
  EnemyManager* self = (EnemyManager*)tolua_tousertype(tolua_S, 1, 0);
  Enemy* boss = self->getBoss();
  tolua_pushusertype(tolua_S, (void*)boss, "Enemy");
  //tolua_register_gc(tolua_S, lua_gettop(tolua_S));
  return 1;
}

static int tolua_VC_EnemyManager_setBoss(lua_State* tolua_S) {
  EnemyManager* self = (EnemyManager*)tolua_tousertype(tolua_S, 1, 0);
  Enemy* boss = (Enemy*)tolua_tousertype(tolua_S, 2, 0);
  self->setBoss(boss);
  return 0;
}

// MessageManager
#pragma mark MessageManager

static int tolua_VC_MessageManager_sharedManager(lua_State* tolua_S) {
  tolua_pushusertype(tolua_S, (void*)MessageManager::sharedManager(), "MessageManager");
  return 1;
}

static int tolua_VC_MessageManager_pushMessage(lua_State* tolua_S) {
  MessageManager* self = (MessageManager*)tolua_tousertype(tolua_S, 1, 0);
  const char* string = tolua_tostring(tolua_S, 2, 0);
  self->pushMessage(string);
  return 0;
}

static int tolua_VC_MessageManager_pushRandomMessageFromLua(lua_State* tolua_S) {
  MessageManager* self = (MessageManager*)tolua_tousertype(tolua_S, 1, 0);
  const char* string = tolua_tostring(tolua_S, 2, 0);
  self->pushRandomMessageFromLua(string);
  return 0;
}

TOLUA_API int tolua_voxchronicle_open(lua_State* tolua_S) {
  tolua_open(tolua_S);
  tolua_reg_types(tolua_S);
  tolua_module(tolua_S, NULL, 0);
  tolua_beginmodule(tolua_S, NULL);
  tolua_constant(tolua_S, "MAX_ROW", MAX_ROW);
  // 技の使用範囲
  tolua_constant(tolua_S, "SkillRangeSingle", SkillRangeSingle);
  tolua_constant(tolua_S, "SkillRangeAll", SkillRangeAll);
  tolua_constant(tolua_S, "SkillRangeHorizontal", SkillRangeHorizontal);
  tolua_constant(tolua_S, "SkillRangeVertical", SkillRangeVertical);
  tolua_constant(tolua_S, "SkillRangeBack", SkillRangeBack);
  tolua_constant(tolua_S, "SkillRangeSelf", SkillRangeSelf);
  tolua_constant(tolua_S, "SkillRangeFront", SkillRangeFront);
  // 技の属性
  tolua_constant(tolua_S, "SkillTypeNone", SkillTypeNone);
  tolua_constant(tolua_S, "SkillTypeNormal", SkillTypeNormal);
  tolua_constant(tolua_S, "SkillTypePhysical", SkillTypePhysical);
  tolua_constant(tolua_S, "SkillTypeMagical", SkillTypeMagical);
  // キャラの種別
  tolua_constant(tolua_S, "CharacterTypeVox", CharacterTypeVox);
  tolua_constant(tolua_S, "CharacterTypeLaska", CharacterTypeLaska);
  // 敵キャラのアイテム
  tolua_constant(tolua_S, "EnemyItemNone", EnemyItemNone);
  tolua_constant(tolua_S, "EnemyItemShield", EnemyItemShield);
  tolua_constant(tolua_S, "EnemyItemBarrier", EnemyItemBarrier);
  // 音楽セットのタイプ
  tolua_constant(tolua_S, "MusicSetTypeWay", MusicSetTypeWay);
  tolua_constant(tolua_S, "MusicSetTypeBoss", MusicSetTypeBoss);
  // StatusLayerのタグ
  tolua_constant(tolua_S, "MaxHPLabelTag", MaxHPLabelTag);
  tolua_constant(tolua_S, "CurrentHPLabelTag", CurrentHPLabelTag);
  tolua_constant(tolua_S, "LevelLabelTag", LevelLabelTag);
  tolua_constant(tolua_S, "LifeGaugeBackgroundTag", LifeGaugeBackgroundTag);
  tolua_constant(tolua_S, "LifeGaugeTag", LifeGaugeTag);
  tolua_constant(tolua_S, "MPMarkerTag", MPMarkerTag);
  // ControllerFrameType
  tolua_constant(tolua_S, "ControllerFrameTypeNone", ControllerFrameTypeNone);
  tolua_constant(tolua_S, "ControllerFrameTypeCommon", ControllerFrameTypeCommon);
  tolua_constant(tolua_S, "ControllerFrameTypeFull", ControllerFrameTypeFull);
  // Skillクラス
  tolua_cclass(tolua_S, "Skill", "Skill", "CCObject", NULL);
  tolua_beginmodule(tolua_S, "Skill");
  tolua_function(tolua_S, "getPower", tolua_VC_Skill_getPower);
  tolua_endmodule(tolua_S);
  // Enemyクラス
  tolua_cclass(tolua_S, "Enemy", "Enemy", "CCSprite", NULL);
  tolua_beginmodule(tolua_S, "Enemy");
  tolua_function(tolua_S, "getRow", tolua_VC_Enemy_getRow);
  tolua_function(tolua_S, "moveRow", tolua_VC_Enemy_moveRow);
  tolua_function(tolua_S, "setRow", tolua_VC_Enemy_setRow);
  tolua_function(tolua_S, "getCol", tolua_VC_Enemy_getCol);
  tolua_function(tolua_S, "getRegister", tolua_VC_Enemy_getRegister);
  tolua_function(tolua_S, "setRegister", tolua_VC_Enemy_setRegister);
  tolua_function(tolua_S, "hasRegister", tolua_VC_Enemy_hasRegister);
  tolua_function(tolua_S, "setAnimationClip", tolua_VC_Enemy_setAnimationClip);
  tolua_function(tolua_S, "setDefaultAnimationClip", tolua_VC_Enemy_setDefaultAnimationClip);
  tolua_function(tolua_S, "getName", tolua_VC_Enemy_getName);
  tolua_function(tolua_S, "getHP", tolua_VC_Enemy_getHP);
  tolua_endmodule(tolua_S);
  // CharacterManagerクラス
  tolua_cclass(tolua_S, "CharacterManager", "CharacterManager", "CCObject", NULL);
  tolua_beginmodule(tolua_S, "CharacterManager");
  tolua_function(tolua_S, "setShield", tolua_VC_CharacterManager_setShield);
  tolua_function(tolua_S, "addTension", tolua_VC_CharacterManager_addTension);
  tolua_function(tolua_S, "getTension", tolua_VC_CharacterManager_getTension);
  tolua_function(tolua_S, "changeCharacter", tolua_VC_CharacterManager_changeCharacter);
  tolua_function(tolua_S, "setLevel", tolua_VC_CharacterManager_setLevel);
  tolua_function(tolua_S, "getLevel", tolua_VC_CharacterManager_getLevel);
  tolua_function(tolua_S, "addHP", tolua_VC_CharacterManager_addHP);
  tolua_function(tolua_S, "addMP", tolua_VC_CharacterManager_addMP);
  tolua_function(tolua_S, "getDrumLevel", tolua_VC_CharacterManager_getDrumLevel);
  tolua_function(tolua_S, "setDrumLevel", tolua_VC_CharacterManager_setDrumLevel);
  tolua_function(tolua_S, "damage", tolua_VC_CharacterManager_damage);
  tolua_function(tolua_S, "getHP", tolua_VC_CharacterManager_getHP);
  tolua_function(tolua_S, "getMP", tolua_VC_CharacterManager_getMP);
  tolua_function(tolua_S, "getMaxHP", tolua_VC_CharacterManager_getMaxHP);
  tolua_function(tolua_S, "getMaxMP", tolua_VC_CharacterManager_getMaxMP);
  tolua_endmodule(tolua_S);
  // EnemyManagerクラス
  tolua_cclass(tolua_S, "EnemyManager", "EnemyManager", "CCLayer", NULL);
  tolua_beginmodule(tolua_S, "EnemyManager");
  tolua_function(tolua_S, "nextTurn", tolua_VC_EnemyManager_nextTurn);
  tolua_function(tolua_S, "popEnemyAt", tolua_VC_EnemyManager_popEnemyAt);
  tolua_function(tolua_S, "getBoss", tolua_VC_EnemyManager_getBoss);
  tolua_function(tolua_S, "setBoss", tolua_VC_EnemyManager_setBoss);
  tolua_endmodule(tolua_S);
  // EnemySkillクラス
  tolua_cclass(tolua_S, "EnemySkill", "EnemySkill", "CCObject", NULL);
  tolua_beginmodule(tolua_S, "EnemySkill");
  tolua_endmodule(tolua_S);
  // MessageManagerクラス
  tolua_cclass(tolua_S, "MessageManager", "MessageManager", "CCObject", NULL);
  tolua_beginmodule(tolua_S, "MessageManager");
  tolua_function(tolua_S, "sharedManager", tolua_VC_MessageManager_sharedManager);
  tolua_function(tolua_S, "pushMessage", tolua_VC_MessageManager_pushMessage);
  tolua_function(tolua_S, "pushRandomMessageFromLua", tolua_VC_MessageManager_pushRandomMessageFromLua);
  tolua_endmodule(tolua_S);
  return 1;
}