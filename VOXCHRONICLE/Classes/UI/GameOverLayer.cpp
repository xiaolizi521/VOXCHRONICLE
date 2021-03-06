//
//  GameOverLayer.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/1/31.
//
//

#include "GameOverLayer.h"
#include "SimpleAudioEngine.h"
#include "FileUtils.h"
#include "TitleScene.h"
#include "macros.h"
#include "MessageManager.h"
#include "PlayLog.h"
#include "BufferCache.h"

#include "MainMenuScene.h"
#include "FreePlayScene.h"
#include "TutorialScene.h"

GameOverLayer::GameOverLayer(MainScene* main) {
  _main = main;
  this->setTouchEnabled(true);
  // 巡回参照してた
  this->buildUI();
}

GameOverLayer::~GameOverLayer() {
}

void GameOverLayer::buildUI() {
  CCSprite* gameover = CCSprite::create("gameover_label.png");
  CCDirector* director = CCDirector::sharedDirector();
  CCPoint center = CCPointMake(director->getWinSize().width / 2, director->getWinSize().height / 2);
  gameover->setPosition(center);
  gameover->runAction(CCSequence::create(CCDelayTime::create(3.0),
                                         CCMoveTo::create(0.1, ccp(director->getWinSize().width / 2, 200)),
                                         CCCallFunc::create(this, callfunc_selector(GameOverLayer::addGameOverButtons)),
                                         NULL));
  this->addChild(gameover);
}

void GameOverLayer::addGameOverButtons() {
  CCMenu* menu = CCMenu::create(CCMenuItemImage::create("replay.png", "replay_pressed.png", this, menu_selector(GameOverLayer::replayButtonPressed)),
                                CCMenuItemImage::create("title.png", "title_pressed.png", this, menu_selector(GameOverLayer::titleButtonPressed)),
                                NULL);
  CCDirector* director = CCDirector::sharedDirector();
  menu->setPosition(ccp(director->getWinSize().width / 2, 90));
  menu->alignItemsVerticallyWithPadding(20);
  this->addChild(menu);
}

void GameOverLayer::replayButtonPressed(CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  
  CCScene* scene = CCScene::create();
  _main->teardown();
  Map* newMap = new Map(_main->getMap()->getIdentifier().c_str());
  PlayLog* oldLog = _main->getPlayLog();
  
  MainScene* newScene = new MainScene();
  newScene->autorelease();
  if (_main->isBossBattle()) {
    newScene->init(newMap, newMap->getMaxLevel());
  } else {
    newScene->init(newMap);
  }
  newScene->setIsContinue(true); // コンティニュー状態に
  newScene->setBackScene(_main->getBackScene()); // 戻り位置を継承
  scene->addChild(newScene);
  newMap->release();
  
  newScene->setPlayLog(oldLog);
  
  CCTransitionFade* transition = CCTransitionFade::create(0.5, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
}

void GameOverLayer::titleButtonPressed(CCObject *sender) {
  _main->teardown();
  CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/decide.mp3").c_str());
  CCScene* scene = CCScene::create();
  if (_backScene == MainBackSceneTitle) {
    scene->addChild(TitleScene::create());
  } else if (_backScene == MainBackSceneMainMenu) {
    MainMenuScene* menu = new MainMenuScene(true);
    menu->autorelease();
    scene->addChild(menu);
  } else if (_backScene == MainBackSceneSoundTest) {
    FreePlayScene* layer = FreePlayScene::create("soundtest.lua", false);
    scene->addChild(layer);
  } else if (_backScene == MainBackSceneFreePlay) {
    FreePlayScene* layer = FreePlayScene::create("freeplay.lua", false);
    scene->addChild(layer);
  } else if (_backScene == MainBackSceneTutorial) {
    TutorialLayer* layer = TutorialLayer::create();
    scene->addChild(layer);
  } else if (_backScene == MainBackSceneDebug) {
    FreePlayScene* layer = FreePlayScene::create("debug.lua", true);
    scene->addChild(layer);
  }
  CCTransitionFade* transition = CCTransitionFade::create(0.5, scene);
  CCDirector::sharedDirector()->replaceScene(transition);
  VISS::BufferCache::sharedCache()->purgeAllBuffers();
}

void GameOverLayer::setMainBackScene(MainBackScene scene) {
  _backScene = scene;
}

void GameOverLayer::registerWithTouchDispatcher() {
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 200, true);
}

bool GameOverLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
  return true;
}