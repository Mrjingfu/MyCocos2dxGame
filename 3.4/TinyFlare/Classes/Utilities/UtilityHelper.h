//
//  UtilityHelper.h
//  TinyFlare
//
//  Created by wang haibo on 15/3/31.
//
//

#ifndef __TinyFlare__UtilityHelper__
#define __TinyFlare__UtilityHelper__

#include "cocos2d.h"

class UtilityHelper
{
public:
    static bool checkCircleIntersectWithSegment(const cocos2d::Vec2& center, float radius, const cocos2d::Vec2& start, const cocos2d::Vec2& end);
};

#endif /* defined(__TinyFlare__UtilityHelper__) */
