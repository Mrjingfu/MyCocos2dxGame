//
//  Skilllayer.cpp
//  lichuang
//
//  Created by lichuang on 2016/01/13.
//
//

#include "SkillLayer.hpp"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "VoxelExplorer.h"
#include "Player.hpp"
#include "PopupUILayerManager.h"
USING_NS_CC;
SkillLayer::SkillLayer()
{
    m_pSkill    = nullptr;
    m_pMagicPotion = nullptr;
    m_pBloodPotion = nullptr;
    m_pMagicPotionMask = nullptr;
    m_pBloodPotionMask = nullptr;
    m_pSkillProgress = nullptr;
    m_bIsUseSkill   = false;
    m_nMagicPotionId   = -1;
    m_nBloodPotionId = -1;
    m_fCoolTime = 0.0f;
}

SkillLayer::~SkillLayer()
{
    
}

bool SkillLayer::initUi()
{
    if (!WrapperUILayer::initUi())
            return false;
    return load("skillLayer.csb",false);
}
bool SkillLayer::addEvents()
{

    m_pSkill = dynamic_cast<cocos2d::ui::ImageView *>(UtilityHelper::seekNodeByName(m_pRootNode, "skill_icon"));
    if(!m_pSkill)
        return false;
    m_pMagicPotion = dynamic_cast<cocos2d::ui::ImageView *>(UtilityHelper::seekNodeByName(m_pRootNode, "skill_magic_icon"));
    if(!m_pMagicPotion)
        return false;
    m_pBloodPotion = dynamic_cast<cocos2d::ui::ImageView *>(UtilityHelper::seekNodeByName(m_pRootNode, "skill_health_icon"));
    if(!m_pBloodPotion)
        return false;
    m_pMagicPotionMask = dynamic_cast<cocos2d::ui::ImageView *>(UtilityHelper::seekNodeByName(m_pRootNode, "skill_magic_icon_mask"));
    if(!m_pMagicPotionMask)
        return false;
    m_pBloodPotionMask = dynamic_cast<cocos2d::ui::ImageView *>(UtilityHelper::seekNodeByName(m_pRootNode, "skill_health_icon_mask"));
    if(!m_pBloodPotionMask)
        return false;
    
    m_pSkill->addTouchEventListener(CC_CALLBACK_2(SkillLayer::onTouchSkill, this));
    m_pMagicPotion->addTouchEventListener(CC_CALLBACK_2(SkillLayer::onTouchMagic, this));
    m_pBloodPotion->addTouchEventListener(CC_CALLBACK_2(SkillLayer::onTouchBlood, this));
    
    m_pSkillProgress = ProgressTimer::create(cocos2d::Sprite::createWithSpriteFrameName("ui_skill_prog.png"));
    m_pSkillProgress->setType(cocos2d::ProgressTimer::Type::RADIAL);
    m_pSkillProgress->setReverseDirection(true);
    m_pSkillProgress->setPosition(m_pSkill->getContentSize()*0.5);
    m_pSkill->addChild(m_pSkillProgress);
    
    m_pMagicPotion->setTouchEnabled(true);
    m_pSkill->setTouchEnabled(true);
    m_pBloodPotion->setTouchEnabled(true);
    refreshUIView();
    refreshSkillView();
    return true;
}
void SkillLayer::refreshUIView()
{
    std::string imgName = "ui_skill_lock.png" ;
    if (m_pMagicPotion && m_pBloodPotion)
    {
        m_nMagicPotionId = -1;
        m_nBloodPotionId = -1;
        std::vector<PickableItemProperty*> items = PlayerProperty::getInstance()->getPlayerBag();
        std::sort(items.begin(), items.end(), [](PickableItemProperty* item1,PickableItemProperty* item2){
                return item1->getPickableItemType() < item2->getPickableItemType();
        });
        for (auto iter =items.begin(); iter!=items.end(); ++iter)
        {
            if (*iter) {
                PickableItemProperty* item = (*iter);
                if (item->getPickableItemType()>=PickableItem::PIT_POTION_MINORHEALTH && item->getPickableItemType()<=PickableItem::PIT_POTION_HEALTH)
                {
                    m_nBloodPotionId = item->getInstanceID();
                    break;
                }
            }
        }
        for (auto iter =items.begin(); iter!=items.end(); ++iter)
        {
            if (*iter) {
                PickableItemProperty* item = (*iter);
                if (item->getPickableItemType()>=PickableItem::PIT_POTION_MINORMANA && item->getPickableItemType()<=PickableItem::PIT_POTION_MANA)
                {
                    m_nMagicPotionId = item->getInstanceID();
                    break;
                }
            }
        }
        

        
        if (m_nMagicPotionId !=-1)
            m_pMagicPotionMask->setVisible(false);
        else
             m_pMagicPotionMask->setVisible(true);

        
        if (m_nBloodPotionId !=-1)
            m_pBloodPotionMask->setVisible(false);
        else
            m_pBloodPotionMask->setVisible(true);;

    }
    
}
void SkillLayer::refreshSkillView()
{
    std::string imgName = "ui_skill_lock.png" ;
    if (m_pSkill) {
        m_pSkillProgress->setPercentage(100);
        m_bIsUseSkill = false;
        CChaosNumber secondWeaponId =  PlayerProperty::getInstance()->getEquipedSecondWeaponID();
        
        if ( secondWeaponId.GetLongValue() != -1)
        {
            
            PickableItemProperty* item = PlayerProperty::getInstance()->getItemFromBag( secondWeaponId);
            if (item) {
                PickableItem::PickableItemType type = item->getPickableItemType();
                if (type >= PickableItem::PIT_BOW_SHORTBOW && type <= PickableItem::PIT_BOW_PRO_GOLDENBOW)//魔法箭
                {
                    imgName = "ui_skill_arrow.png";
                    m_bIsUseSkill = true;
                    m_fCoolTime = Player::m_fMagicArrowColdDownTime;

                }
                else if(type >= PickableItem::PIT_STAFF_OAKSTAFF && type <= PickableItem::PIT_STAFF_PRO_MONKSTAFF)//火球
                {
                    imgName = "ui_skill_fire.png";
                    m_bIsUseSkill = true;
                    m_fCoolTime = Player::m_fFireBallColdDownTime;

                }
                else if(type >= PickableItem::PIT_SHIELD_WOODENSHIELD && type <= PickableItem::PIT_SHIELD_PRO_TOWERSHIELD)//格挡
                {
                    imgName = "ui_skill_block.png";
                    m_bIsUseSkill = true;
                    m_fCoolTime = Player::m_fBlockRateUpColdDownTime;

                }
                else
                    imgName = "ui_skill_lock.png";
            }
            
        }
        if (m_bIsUseSkill){
                skillProgressAction();
        }else
            m_pSkillProgress->setPercentage(0);
        
        m_pSkill->loadTexture(imgName,TextureResType::PLIST);
        m_pSkillProgress->setCameraMask((unsigned short)m_nCamerFlag);
        m_pSkill->setCameraMask((unsigned short)m_nCamerFlag);
    }

}
void SkillLayer::onTouchBlood(Ref* ref,Widget::TouchEventType type)
{
       switch (type) {
        case Widget::TouchEventType::BEGAN:
               clickEffect();
            if (m_pBloodPotion) {
                m_pBloodPotion->setScale(0.45);
            }
            break;
        case Widget::TouchEventType::ENDED:
            if (m_pBloodPotion) {
                m_pBloodPotion->stopAllActions();
                m_pBloodPotion->runAction(Sequence::create(EaseBackInOut::create(ScaleTo::create(0.2f, 0.5f)),CallFunc::create([this](){
                    if (m_nBloodPotionId!=-1)
                    {
                        PlayerProperty::getInstance()->usePotion(m_nBloodPotionId);
                        
                    }else{
                       PopupUILayerManager::getInstance()->showStatusImport(TIP_NEGATIVE, UtilityHelper::getLocalStringForUi("SKILL_TIP_NOT_BLOOD_POTION"));
                    }
                
                }),nullptr));
            }
            break;
        case Widget::TouchEventType::MOVED:
        case Widget::TouchEventType::CANCELED:
           if (m_pBloodPotion) {
               m_pBloodPotion->stopAllActions();
               m_pBloodPotion->runAction(EaseBackInOut::create(ScaleTo::create(0.2f, 0.5f)));
           }
               break;
            break;
        default:
            break;
    }
}
void SkillLayer::onTouchMagic(Ref* ref,Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            clickEffect();
            if (m_pMagicPotion) {
                m_pMagicPotion->setScale(0.45);
            }
            break;
        case Widget::TouchEventType::ENDED:
            if (m_pMagicPotion) {
                m_pMagicPotion->stopAllActions();
                m_pMagicPotion->runAction(Sequence::create(EaseBackInOut::create(ScaleTo::create(0.2f, 0.5f)),CallFunc::create([this](){
                    if (m_nMagicPotionId!=-1)
                    {
                        PlayerProperty::getInstance()->usePotion(m_nMagicPotionId);
                        
                    }else{
                        PopupUILayerManager::getInstance()->showStatusImport(TIP_NEGATIVE, UtilityHelper::getLocalStringForUi("SKILL_TIP_NOT_MAGIC_POTION"));
                    }
                    
                }),nullptr));
            }
             break;
       case Widget::TouchEventType::MOVED:
       case Widget::TouchEventType::CANCELED:
            if (m_pMagicPotion) {
                m_pMagicPotion->stopAllActions();
                m_pMagicPotion->runAction(EaseBackInOut::create(ScaleTo::create(0.2f, 0.5f)));
            }
            break;
        default:
            break;
    }
}
void SkillLayer::onTouchSkill(Ref* ref,Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            clickEffect();
            if (m_pSkill) {
                m_pSkill->setScale(0.65);
            }
             break;
        case Widget::TouchEventType::ENDED:
                if (m_pSkill) {
                    m_pSkill->runAction(Sequence::create(EaseBackInOut::create(ScaleTo::create(0.2f, 0.7f)),CallFunc::create([this](){
                        if (m_bIsUseSkill )
                        {
                            if(m_pSkillProgress->getPercentage()==0)
                            {
                                if(VoxelExplorer::getInstance()->handlePlayerUseSkill())
                                    refreshSkillView();
                                
                            }else
                            {
                                PopupUILayerManager::getInstance()->showStatusImport(TIP_NEGATIVE, UtilityHelper::getLocalStringForUi("SKILL_TIP_COOLING"));
                            }
                        }else
                        {
                            PopupUILayerManager::getInstance()->showStatusImport(TIP_NEGATIVE, UtilityHelper::getLocalStringForUi("SKILL_TIP_NOT_EQUIP"));
                        }
                        
                    }),nullptr));
               
            }
            break;
        case Widget::TouchEventType::MOVED:
        case Widget::TouchEventType::CANCELED:
            if (m_pSkill) {
                m_pSkill->stopAllActions();
                m_pSkill->runAction(EaseBackInOut::create(ScaleTo::create(0.2f, 0.7f)));
            }
             break;
        default:
            break;
    }
}
void SkillLayer::skillProgressAction()
{
    m_pSkillProgress->stopAllActions();
    m_pSkillProgress->runAction(Sequence::create(ProgressTo::create(m_fCoolTime, 0),CallFunc::create([this](){
        
        if (m_pSkill) {
            m_pSkillProgress->setPercentage(0);
            m_pSkill->stopAllActions();
            m_pSkill->runAction(Sequence::create(EaseBackInOut::create(ScaleTo::create(0.1f, 0.65f)), EaseBackInOut::create(ScaleTo::create(0.1f, 0.7f)),nullptr));
        }
        
    }),nullptr));
}
