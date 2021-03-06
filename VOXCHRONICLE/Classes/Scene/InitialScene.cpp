//
//  InitialScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/5/4.
//
//

#include "InitialScene.h"
#include "FileUtils.h"
#include "LuaObject.h"
#include "KWAlert.h"
#include "Map.h"
#include "MainScene.h"
#include "MainMenuScene.h"

bool InitialScene::init() {
  this->setTouchEnabled(false);
  
  return true;
}

void InitialScene::onEnterTransitionDidFinish() {
  LuaObject* setting = LuaObject::create("setting");
  CCDirector* director = CCDirector::sharedDirector();
  CCArray* names = CCArray::create(CCString::create("はい"), CCString::create("いいえ"), NULL);
  KWAlert* alert = new KWAlert("dialog_window.png", names);
  alert->setPosition(ccp(director->getWinSize().width / 2.0, director->getWinSize().height / 2.0));
  alert->autorelease();
  this->addChild(alert);
  alert->setText(setting->getString("introductionMessage"));
  alert->setDelegate(this);
  alert->show();
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/window_open.mp3").c_str());
}

void InitialScene::clickedButtonAtIndex(KWAlert *alert, int index) {
  alert->setEnabled(false);
  if (index == 0) {
    this->scheduleOnce(schedule_selector(InitialScene::onGotoTutorial), 2.f);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/tutorial_decide.mp3").c_str());
    this->setTouchEnabled(false);
  } else {
    alert->dismiss();
    CCDirector* director = CCDirector::sharedDirector();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/window_close.mp3").c_str());
    MainMenuScene* menu = new MainMenuScene(true);
    menu->autorelease();
    CCScene* scene = CCScene::create();
    scene->addChild(menu);
    CCTransitionFade* transition = CCTransitionFade::create(1.0f, scene);
    director->replaceScene(transition);
  }
}

void InitialScene::onGotoTutorial() {
  SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
  Map* map = new Map("tutorial0"); // ハードコード安定
  map->autorelease();
  MainScene* layer = new MainScene();
  layer->autorelease();
  layer->init(map);
  layer->setBackScene(MainBackSceneTutorial);
  CCScene* scene = CCScene::create();
  scene->addChild(layer);
  CCTransitionFade* fade = CCTransitionFade::create(0.5f, scene);
  CCDirector::sharedDirector()->replaceScene(fade);
}