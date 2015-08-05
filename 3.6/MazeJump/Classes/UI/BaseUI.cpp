//
//  BaseUI.cpp
//
//
//
//

#include "BaseUI.h"
#include "GameConst.h"
USING_NS_CC;


BaseUI::BaseUI()
{
    m_uiLayer = nullptr;
    m_maskLayer = nullptr;
    m_dialogLayer = nullptr;
    m_isShowDialog = false;
}
BaseUI::~BaseUI()
{
}
void BaseUI::onEnter()
{
    Layout::onEnter();
    auto size = Director::getInstance()->getVisibleSize();
    
    
    m_maskLayer = cocos2d::Layer::create();
    m_maskLayer->setName(LAYER_NAME_MASK);
    addChild(m_maskLayer,LAYER_MASK,LAYER_MASK);
    
    
    auto maskLayer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 150));
    maskLayer->setContentSize(size);
    m_maskLayer->addChild(maskLayer);
    m_maskLayer->setVisible(false);
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan =  [this](Touch * ,Event *)
    {
        if (m_isShowDialog) {
            return true;
        }else{
            return false;
        }
        
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,m_maskLayer);
    m_uiLayer = cocos2d::Layer::create();
    m_uiLayer->setName(LAYER_NAME_UI);
    addChild(m_uiLayer,LAYER_UI,LAYER_UI);
    
    m_dialogLayer = cocos2d::Layer::create();
    m_dialogLayer->setName(LAYER_NAME_DIALOG);
    addChild(m_dialogLayer,LAYER_DIALOG,LAYER_DIALOG);
    m_dialogLayer->setVisible(false);
   
    

}
void BaseUI::onExit()
{
    Layout::onExit();
}
cocos2d::Layer* BaseUI::getLayer(std::string layerName)
{
    return static_cast<Layer*>(this->getChildByName(layerName));
}

