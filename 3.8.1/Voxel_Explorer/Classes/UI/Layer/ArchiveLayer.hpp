//
//  Archivelayer.hpp
//  lichuang
//
//  Created by lichuang on 2016/01/11.
//
//

#ifndef Archivelayer_hpp
#define Archivelayer_hpp

#include "WrapperUILayer.h"

class ArchiveLayer : public WrapperUILayer
{   
public:
    ArchiveLayer();
    virtual ~ArchiveLayer();
    
    CREATE_FUNC(ArchiveLayer);
    
    virtual bool initUi() override;
    virtual bool addEvents() override;
    void setArchiveDesc(const std::string& desc);
    void setArchiveName(const std::string& name){m_sArchiveName = name;}
    void onArchive(){m_bisArchive = true;};
private:
    void onClickStarGame(Ref* ref);
    void onClickDelGame(Ref* ref);
protected:
    
    bool m_bisArchive;
    std::string m_sArchiveName;
    cocos2d::ui::ImageView * m_pArchiveImg;
    cocos2d::ui::Text * m_pArchiveDesc;
    cocos2d::ui::Button * m_pArchiveBtnDel;
   
};

#endif /* Archivelayer_hpp */

