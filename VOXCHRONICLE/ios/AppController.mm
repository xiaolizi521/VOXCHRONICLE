/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"
#import "CCAchievementManager.h"
#import <GameKit/GameKit.h>
#import "CCAchievementManager.h"
#import "SaveData.h"

#import "RootViewController.h"
#import "TestFlight.h"

#import "OALSimpleAudio.h"

@implementation AppController

#define TEAM_TOKEN @"bc5125eaeaeb391c196c7a3ac8a311a5_MTMxMDg4MjAxMi0wOS0xMSAyMTowMzo0Mi41NTY3Njg"

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

/*
 My Apps Custom uncaught exception catcher, we do special stuff here, and TestFlight takes care of the rest
 */
void HandleExceptions(NSException *exception) {
  NSLog(@"This is where we save the application data during a exception");
  // Save application data on crash
}
/*
 My Apps Custom signal catcher, we do special stuff here, and TestFlight takes care of the rest
 */
void SignalHandler(int sig) {
  NSLog(@"This is where we save the application data during a signal");
  // Save application data on crash
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  
  // Override point for customization after application launch.
  
#ifdef TESTING
  // installs HandleExceptions as the Uncaught Exception Handler
  NSSetUncaughtExceptionHandler(&HandleExceptions);
  // create the signal action structure
  struct sigaction newSignalAction;
  // initialize the signal action structure
  memset(&newSignalAction, 0, sizeof(newSignalAction));
  // set SignalHandler as the handler in the signal action structure
  newSignalAction.sa_handler = &SignalHandler;
  // set SignalHandler as the handlers for SIGABRT, SIGILL and SIGBUS
  sigaction(SIGABRT, &newSignalAction, NULL);
  sigaction(SIGILL, &newSignalAction, NULL);
  sigaction(SIGBUS, &newSignalAction, NULL);
  // Call takeOff after install your own unhandled exception and signal handlers
  [TestFlight takeOff:TEAM_TOKEN]; // TestFlight SDK
  [TestFlight setDeviceIdentifier:[[UIDevice currentDevice] uniqueIdentifier]];
#endif
  
  // Add the view controller's view to the window and display.
  window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
  EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                   pixelFormat: kEAGLColorFormatRGBA8
                                   depthFormat: GL_DEPTH_COMPONENT16
                            preserveBackbuffer: NO
                                    sharegroup:nil
                                 multiSampling:NO
                               numberOfSamples:0];
  
  // Use RootViewController manage EAGLView
  viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
  viewController.wantsFullScreenLayout = YES;
  viewController.view = __glView;
  
  // 起動回数カウント
  SaveData::sharedData()->addCountFor(SaveDataCountKeyBoot);
  int count = SaveData::sharedData()->getCountFor(SaveDataCountKeyBoot);
  CCLog("boot count = %d", count);
  SaveData::sharedData()->save();
  
  // GameCenter
  float iosVersion = [[[UIDevice currentDevice] systemVersion] floatValue];
  GKLocalPlayer* localPlayer = [GKLocalPlayer localPlayer];
  if (iosVersion >= 6) { // iOS6向け
    localPlayer.authenticateHandler = ^(UIViewController* ui, NSError* error) {
      if (ui != nil) {
        //[viewController presentModalViewController:ui animated:YES];
      } else if (localPlayer.isAuthenticated) {
        NSLog(@"authentication is completed");
        [self onCompleteAuthenticationToGameCenter];
      } else {
        NSLog(@"%@", error);
      }
    };
  } else {
    [localPlayer authenticateWithCompletionHandler:^(NSError *error) {
      NSLog(@"%@", error);
      if (error == nil) {
        NSLog(@"authentication is completed");
        [self onCompleteAuthenticationToGameCenter];
      }
    }];
  }
  
  // カウント集表示
  SaveData* data = SaveData::sharedData();
  CCLog("dead = %d", data->getCountFor(SaveDataCountKeyDead));
  CCLog("defeat = %d", data->getCountFor(SaveDataCountKeyDefeat));
  CCLog("hitDamage = %d", data->getCountFor(SaveDataCountKeyHitDamage));
  CCLog("mpmiss = %d", data->getCountFor(SaveDataCountKeyMPMiss));
  CCLog("turn = %d", data->getCountFor(SaveDataCountKeyTurn));
  CCLog("attackDamage = %d", data->getCountFor(SaveDataCountKeyAttackDamage));
  CCLog("dictionaryCount = %d", data->getCountFor(SaveDataCountKeyDictionaryCount));
  
  // Set RootViewController to window
  // Fix orientation problem on iOS6
  if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0) {
    // warning: addSubView doesn't work on iOS6
    [window addSubview: viewController.view];
  } else {
    // use this mehod on ios6
    [window setRootViewController:viewController];
  }
  [window makeKeyAndVisible];
  
  CCLog("%f", [window bounds].size.width);
  if ([window bounds].size.height == 568) {
    // iPhone5
    CGAffineTransform transform = __glView.transform;
    CGAffineTransform move = CGAffineTransformTranslate(transform, 44 * 1136.f / 960.f, 0);
    CGAffineTransform trans = CGAffineTransformScale(move, 1136.f / 960.f, 1.0f);
    [__glView setTransform:trans];
  }
  
  [[UIApplication sharedApplication] setStatusBarHidden: YES];
  [OALSimpleAudio sharedInstance].reservedSources = 6;
  
  cocos2d::CCApplication::sharedApplication()->run();
  
  return YES;
}

- (void)onCompleteAuthenticationToGameCenter {
  [GKAchievement loadAchievementsWithCompletionHandler:^(NSArray *achievements, NSError *error) {
    for (GKAchievement* achievement in achievements) {
      NSString* name = achievement.identifier;
      const char* identifier = [name UTF8String];
      CCLog("unlocked %s", identifier);
      SaveData::sharedData()->setUnlockedAchievement(identifier);
    }
  }];
}


- (void)applicationWillResignActive:(UIApplication *)application {
  /*
   Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
   Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
   */
  cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
  /*
   Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
   */
  cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
  /*
   Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
   If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
   */
  cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
  /*
   Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
   */
  cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
  /*
   Called when the application is about to terminate.
   See also applicationDidEnterBackground:.
   */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
  /*
   Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
   */
#if TESTING
  TFLog(@"memory warning!!!!!!!!!!");
  [TestFlight submitFeedback:@"メモリリークしたんでなんとかしてください"];
#endif
  CCTextureCache::sharedTextureCache()->removeUnusedTextures();
  Species::purgeSpeciesCache();
  SimpleAudioEngine::sharedEngine()->unloadAllEffect();
}

- (void)dealloc {
  [super dealloc];
}


@end

