//
//  BlinkLayer.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/27.
//
//

#ifndef __VOXCHRONICLE__BlinkLayer__
#define __VOXCHRONICLE__BlinkLayer__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class BlinkLayer :public CCNode {
 private:
   void suicide();
 public:
  BlinkLayer(ccColor4B color, float delay);
};

#endif /* defined(__VOXCHRONICLE__BlinkLayer__) */
