//
//  GameUILayer.h
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/16.
//
//

#ifndef GameUILayer_h
#define GameUILayer_h

#include "WrapperUILayer.h"

class GameUILayer:public WrapperUILayer {
    
public:
    GameUILayer();
    virtual ~GameUILayer();
public:
    CREATE_FUNC(GameUILayer);
    virtual bool addEvents();
};

#endif /* GameUILayer_h */
