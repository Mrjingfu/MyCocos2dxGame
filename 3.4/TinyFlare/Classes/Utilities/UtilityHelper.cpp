//
//  UtilityHelper.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/3/31.
//
//

#include "UtilityHelper.h"
USING_NS_CC;
bool UtilityHelper::checkCircleIntersectWithSegment(const Vec2& center, float radius, const Vec2& start, const Vec2& end)
{
    bool ret = false;
    Vec2 d = (end - start).getNormalized();
    Vec2 e = center - start;
    
    float a = e.dot(d);
    
    float a2 = a*a;
    float e2 = center.distanceSquared(start);
    float r2 = radius*radius;
    
    if ((r2 + a2) < e2)
        ret = false;
    else
    {
        Vec2 v1 = (start - center).getNormalized();
        Vec2 v2 = (end - center).getNormalized();
        float f = v1.dot(v2);
        if(f > 0)
            ret = false;
        else
            ret = true;
    }
    ////这个判断算法只是粗略检测，当两点之间距离是小于半径2倍时会穿透。
    return ret;
}