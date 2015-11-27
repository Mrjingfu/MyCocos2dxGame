//
//  GameInfoLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/27.
//
//

#ifndef GameInfoLayer_hpp
#define GameInfoLayer_hpp

#include "WrapperUILayer.h"

class GameInfoLayer :public WrapperUILayer {
    
    GameInfoLayer();
public:
    virtual ~GameInfoLayer();
    CREATE_FUNC(GameInfoLayer);
    virtual bool initUi() override;
    virtual bool addEvents() override;
    virtual void refreshUIView()override;
private:
    cocos2d::ui::Text*       m_pGameGoldNum;            // 金币
    cocos2d::ui::Text*       m_pGameSilverNum;          // 银币
    cocos2d::ui::Text*       m_pGameCopperNum;          // 铜币
    cocos2d::ui::Text*       m_pGameLevelInfoName;      // 关卡名
};

#endif /* GameInfoLayer_hpp */
