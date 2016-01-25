//
//  GameScene.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#include "TestScene.h"
#include "PlayerProperty.hpp"
#include "WrapperUILayer.h"
#include "UtilityHelper.h"
#include "PopupUILayerManager.h"
#include "ItemPopupUI.h"
#include "AchievementManager.h"
#include "AchievePopupUI.h"
#include "NpcDataManager.hpp"
#include "InformationPopupUI.h"
USING_NS_CC;

Scene* TestScene::createScene()
{
    auto scene = Scene::create();
    
    
    cocos2d::Camera* uiCamera = cocos2d::Camera::create();
    uiCamera->setCameraFlag(cocos2d::CameraFlag::USER2);
    scene->addChild(uiCamera);
    
    auto layer = TestScene::create();
    scene->addChild(layer);
    
    auto popupLayer = Layer::create();
    scene->addChild(popupLayer);
    PopupUILayerManager::getInstance()->setParentLayer(popupLayer);
    return scene;
}
TestScene::TestScene()
{

}
void TestScene::onEnter()
{
    WrapperUILayer::onEnter();
    
}
void TestScene::onExit()
{
    PopupUILayerManager::getInstance()->onExitScene();
    WrapperUILayer::onExit();
}

bool TestScene::initUi()
{
    
    
    if (!WrapperUILayer::initUi())
        return false;
    return load("testlayer.csb");
}
bool TestScene::addEvents()
{
    Layout* itemlayer = dynamic_cast<Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "testlayer_item"));
    if(!itemlayer)
        return itemlayer;
    
    TGridView* m_pGridView = TGridView::create();
    m_pGridView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pGridView->setContentSize(cocos2d::Size(itemlayer->getContentSize().width-10,itemlayer->getContentSize().height-7));
    m_pGridView->setCol(1);
    m_pGridView->setPosition(itemlayer->getContentSize()*0.5);
    m_pGridView->setScrollBarWidth(5);
    m_pGridView->setScrollBarColor(Color3B::WHITE);
    m_pGridView->setScrollBarPositionFromCornerForVertical(cocos2d::Vec2(0,0));
    m_pGridView->setItemsMargin(cocos2d::Size(1,3.5));
    m_pGridView->setFrameMargin(cocos2d::Size(7,4));
    m_pGridView->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    itemlayer->addChild(m_pGridView);

    
    
//  testItem(m_pGridView);
//  testAchieve(m_pGridView);
//  testNpcInfo(m_pGridView);
//  testRandom(m_pGridView);
    
    return true;
}
void TestScene::selectAchieveEvent(Ref *pSender, TGridView::EventType type)
{
    if (type==TGridView::EventType::ON_SELECTED_ITEM_END)
    {
        TGridView* gridView = static_cast<TGridView*>(pSender);
        TextBMFont* itemTest = static_cast<TextBMFont*>(gridView->getItem(gridView->getCurSelectedIndex()));
        cocos2d::Vector<AchieveProperty*> achieveVector = AchievementManager::getInstance()->getAllAchieves();
        for (int i=0; i<achieveVector.size();i++)
        {
            AchieveProperty*prop = achieveVector.at(i);
            if (itemTest->getString() == prop->getAchieveIDName()) {
                PopupUILayerManager::getInstance()->showAchieveItem(prop->getAchieveIcon(), prop->getAchieveName(), prop->getTargetDesc());
                itemTest->setColor(Color3B::RED);
                break;
            }
        }
    }
}
void TestScene::selectNpcInfoEvent(Ref *pSender, TGridView::EventType type,cocos2d::ValueVector valueVector)
{
    if (type==TGridView::EventType::ON_SELECTED_ITEM_END)
    {
        TGridView* gridView = static_cast<TGridView*>(pSender);
        TextBMFont* itemTest = static_cast<TextBMFont*>(gridView->getItem(gridView->getCurSelectedIndex()));
        if (itemTest) {
            int index = Value(itemTest->getString()).asInt();
            InformationPopupUI* popup = static_cast<InformationPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupRandomMsg));
            if (popup) {
                popup->setInfoVector(valueVector.at(index).asValueVector());
            }
            itemTest->setColor(Color3B::BLUE);
        }
    }
}
void TestScene::selectRandomEvent(Ref *pSender, TGridView::EventType type,cocos2d::ValueVector valueVector)
{
    if (type==TGridView::EventType::ON_SELECTED_ITEM_END)
    {
        TGridView* gridView = static_cast<TGridView*>(pSender);
        TextBMFont* itemTest = static_cast<TextBMFont*>(gridView->getItem(gridView->getCurSelectedIndex()));
        if (itemTest) {
            int index = Value(itemTest->getString()).asInt();
            InformationPopupUI* popup = static_cast<InformationPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupRandomMsg));
            if (popup) {
                popup->setInfoDesc(valueVector.at(index).asValueMap()["EVENT_DESC"].asString());
            }
            itemTest->setColor(Color3B::BLUE);
        }
    }
}
void TestScene::selectTipsEvent(Ref *pSender, TGridView::EventType type)
{
    if (type==TGridView::EventType::ON_SELECTED_ITEM_END)
    {
        TGridView* gridView = static_cast<TGridView*>(pSender);
        TextBMFont* itemTest = static_cast<TextBMFont*>(gridView->getItem(gridView->getCurSelectedIndex()));
    }
}
void TestScene::selectItemEvent(cocos2d::Ref *pSender, TGridView::EventType type)
{
    if (type==TGridView::EventType::ON_SELECTED_ITEM_END)
    {
        TGridView* gridView = static_cast<TGridView*>(pSender);
        TextBMFont* itemTest = static_cast<TextBMFont*>(gridView->getItem(gridView->getCurSelectedIndex()));
        PickableItem::PickableItemType itemtype  = PickableItem::PIT_UNKNOWN;
        for(int i=0;i<PickableItem::PIT_UNKNOWN;i++)
        {
            if (itemTest->getString() == PICKABLE_ITEM_NAMES[i]) {
                itemtype = (PickableItem::PickableItemType)i;
                break;
            }
        }
        int  itemId = -1;
       
        for (int i=0; i<PlayerProperty::getInstance()->getPlayerBag().size(); i++) {
            PickableItem::PickableItemType type = PlayerProperty::getInstance()->getPlayerBag()[i]->getPickableItemType();
            if (itemtype == type) {
                itemId = PlayerProperty::getInstance()->getPlayerBag()[i]->getInstanceID();
                break;
            }
        }
        ItemPopupUI* popupItem = static_cast<ItemPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupItem));
        if (popupItem) {
            popupItem->setItemId(itemId);
            itemTest->setColor(Color3B::BLUE);
        }
        
    }
}
void TestScene::testAchieve(TGridView* m_pGridView)
{
    m_pGridView->addEventListener(CC_CALLBACK_2(TestScene::selectAchieveEvent, this));
    ValueMap map;
    AchievementManager::getInstance()->load(map);
    cocos2d::Vector<AchieveProperty*> achieveVector = AchievementManager::getInstance()->getAllAchieves();
    for (int i=0; i<achieveVector.size();i++) {
        AchieveProperty*prop = achieveVector.at(i);
        if (prop) {
            TextBMFont* textItem =TextBMFont::create(prop->getAchieveIDName(), UtilityHelper::getLocalStringForUi("FONT_NAME"));
            textItem->setTouchEnabled(true);
            textItem->setScale(0.5);
            m_pGridView->pushBackCustomItem(textItem);
        }
       
    }
    m_pGridView->forceDoLayout();

}
void TestScene::testNpcInfo(TGridView* m_pGridView)
{
   
    cocos2d::ValueVector m_OldManRoom;
    LanguageType lt= Application::getInstance()->getCurrentLanguage();
    switch (lt) {
        case LanguageType::CHINESE:
            m_OldManRoom = FileUtils::getInstance()->getValueVectorFromFile("npc_info_chinese.plist");
            break;
        default:
            m_OldManRoom = FileUtils::getInstance()->getValueVectorFromFile("npc_info_english.plist");
            break;
    }
     m_pGridView->addEventListener(CC_CALLBACK_2(TestScene::selectNpcInfoEvent, this,m_OldManRoom));
    for (int i=0; i<m_OldManRoom.size();i++) {
       ValueVector itemValue = m_OldManRoom.at(i).asValueVector();
        if (!itemValue.empty()) {
            TextBMFont* textItem =TextBMFont::create(cocos2d::Value(i).asString(), UtilityHelper::getLocalStringForUi("FONT_NAME"));
            textItem->setTouchEnabled(true);
            textItem->setScale(0.5);
            m_pGridView->pushBackCustomItem(textItem);
        }
        
    }
    m_pGridView->forceDoLayout();
}
void TestScene::testRandom(TGridView* m_pGridView)
{
    
    cocos2d::ValueVector m_random;
    LanguageType lt= Application::getInstance()->getCurrentLanguage();
    switch (lt) {
        case LanguageType::CHINESE:
            m_random = FileUtils::getInstance()->getValueVectorFromFile("random_events_chinese.plist");
            break;
        default:
            m_random = FileUtils::getInstance()->getValueVectorFromFile("random_events_chinese.plist");
            break;
    }
    m_pGridView->addEventListener(CC_CALLBACK_2(TestScene::selectRandomEvent, this,m_random));
    for (int i=0; i<m_random.size();i++)
    {
        TextBMFont* textItem =TextBMFont::create(cocos2d::Value(i).asString(), UtilityHelper::getLocalStringForUi("FONT_NAME"));
        textItem->setTouchEnabled(true);
        textItem->setScale(0.5);
        m_pGridView->pushBackCustomItem(textItem);
    }
    m_pGridView->forceDoLayout();

}
void TestScene::testTips(TGridView* m_pGridView)
{
    m_pGridView->addEventListener(CC_CALLBACK_2(TestScene::selectTipsEvent, this));
}
void TestScene::testItem(TGridView* m_pGridView)
{
    m_pGridView->addEventListener(CC_CALLBACK_2(TestScene::selectItemEvent, this));
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_KEY_COPPER, 1,false);
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_KEY_SILVER,1,false);             ///银宝箱钥匙
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_KEY_GOLD,1,false);               ///金宝箱钥匙

    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_DAGGER_DAGGER,1,false);           ///匕首
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_DAGGER_HALFSWORD,1,false);        ///短剑
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_DAGGER_KNIFE,1,false);            ///小刀
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_DAGGER_COLDSTEELDAGGER,1,false);  ///冷钢匕首
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_DAGGER_RIPPERCUTTER,1,false);     ///开膛刀
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_DAGGER_BLUELIGHTDAGGER,1,false);  ///蓝光匕首
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_DAGGER_RUBYDAGGER, 1,false);      ///红宝石匕首
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_DAGGER_PRO_DAGGER,1,false);           ///烛光 Candlelight
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_DAGGER_PRO_HALFSWORD,1,false);        ///星耀 Stars Shine
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_DAGGER_PRO_KNIFE, 1,false);           ///黄金杀手 Gold Killer
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_DAGGER_PRO_COLDSTEELDAGGER,1,false);  ///影子袭击者 Shadow Attacker
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_DAGGER_PRO_RIPPERCUTTER,1,false);     ///六刃 Six Blade
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_DAGGER_PRO_BLUELIGHTDAGGER,1,false);  ///凝云 Frozen Cloud
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_DAGGER_PRO_RUBYDAGGER, 1,false);      ///火舌 Fireflow
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_AXE_HATCHET,1,false);            ///小斧
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_AXE_ADZE, 1,false);              ///手斧
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_AXE_STONEAXE,1,false);           ///石斧
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_AXE_BROADAX, 1,false);           ///大斧
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_AXE_TOMAHAWK, 1,false);          ///战斧
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_AXE_HUGEAXE,  1,false);          ///巨斧
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_AXE_DOUBLEBITAX,1,false);        ///双刃斧 double-bit ax
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_AXE_PRO_HATCHET, 1,false);           ///黑铁 Dark Iron
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_AXE_PRO_ADZE,  1,false);             ///半月 Half Moon
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_AXE_PRO_STONEAXE,1,false);           ///回旋加速器 Cyclotron
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_AXE_PRO_BROADAX, 1,false);           ///熔岩 Molten lava
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_AXE_PRO_TOMAHAWK,1,false);           ///狂战士 Berserker
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_AXE_PRO_HUGEAXE, 1,false);           ///骷髅撕裂者 Skull Splitter
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_AXE_PRO_DOUBLEBITAX,1,false);        ///脑袋 Brainhew
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SWORD_SWORD,  1,false);              ///练习剑
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SWORD_STEELSWORD,1,false);           ///长钢剑
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SWORD_SABRE, 1,false);               ///军刀
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SWORD_HUGESWORD, 1,false);           ///巨剑
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SWORD_TRIANGLESWORD,1,false);        ///三角剑
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SWORD_JAGGEDSWORD,1,false);          ///锯齿剑
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SWORD_CRYSTALSWORD, 1,false);        ///水晶剑
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SWORD_PRO_SWORD, 1,false);               ///红莲 Red Lotus
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SWORD_PRO_STEELSWORD,1,false);           ///一闪 Flash
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SWORD_PRO_SABRE,  1,false);              ///劈风者 Wind Strike
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SWORD_PRO_HUGESWORD, 1,false);           ///阳炎 Solar Flame
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SWORD_PRO_TRIANGLESWORD, 1,false);       ///血之使者 Bloodletters
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SWORD_PRO_JAGGEDSWORD,1,false);          ///锐齿 Sawtooth
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SWORD_PRO_CRYSTALSWORD,1,false);         ///诛神 No God
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_MACE_ROLLINGPIN,1,false);                ///擀面杖
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_MACE_MALLET,1,false);                    ///木棒
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_MACE_MACE, 1,false);                     ///权杖
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_MACE_HAMMER, 1,false);                   ///钉头锤
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_MACE_WOLFFANGSMACE, 1,false);            ///狼牙棒
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_MACE_BONEHAMMER, 1,false);               ///骨锤
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_MACE_SLEDGEHAMMER, 1,false);             ///碎骨大锤
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_MACE_PRO_ROLLINGPIN, 1,false);               ///恐龙骨棒 Dinosaur bone
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_MACE_PRO_MALLET,  1,false);                  ///食人魔之锤 The hammer of     PIT_MACE_PRO_MACE,                      ///红宝石权杖 Ruby Mace
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_MACE_PRO_HAMMER,1,false);                    ///黄金荣耀 Golden glory
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_MACE_PRO_WOLFFANGSMACE, 1,false);            ///众神之锤 Mace of the gods
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_MACE_PRO_BONEHAMMER, 1,false);               ///蓝宝石权杖Sapphire Mace
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_MACE_PRO_SLEDGEHAMMER,1,false);              ///死神之力 Azrael Power
    //PIT_MACE_PRO_END
    
    //PIT_BOW_BEGIN
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_BOW_SHORTBOW,1,false);                   ///短弓
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_BOW_LONGBOW, 1,false);                   ///长弓
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_BOW_HORNBOW, 1,false);                   ///角弓
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_BOW_REFLEXBOW, 1,false);                 ///反曲弓
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_BOW_EAGLEBOW, 1,false);                  ///鹰弓
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_BOW_LAMINATEDBOW, 1,false);              ///复合弓
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_BOW_GOLDENBOW, 1,false);                 ///黄金弓
    //PIT_BOW_END
    
    //PIT_BOW_PRO_BEGIN
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_BOW_PRO_SHORTBOW,1,false);                   ///蝎尾 Scorpion tail
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_BOW_PRO_LONGBOW,1,false);                    ///六面火 Hexfire
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_BOW_PRO_HORNBOW,1,false);                    ///要你命三千 Life Terminator
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_BOW_PRO_REFLEXBOW, 1,false);                 ///影袭 Shadow Impact
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_BOW_PRO_EAGLEBOW, 1,false);                  ///鹰眼 Hawkeye
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_BOW_PRO_LAMINATEDBOW,1,false);               ///绿帽 Green Hat
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_BOW_PRO_GOLDENBOW,  1,false);                ///群星陨落 Starsfall
    //PIT_BOW_PRO_END
    
    //PIT_STAFF_BEGIN
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_STAFF_OAKSTAFF,1,false);                   ///橡木法杖
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_STAFF_FIRSTAFF,1,false);                   ///冷杉法杖
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_STAFF_ASHESSTAFF, 1,false);                ///灰烬法杖
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_STAFF_DEMONSTAFF,1,false);                 ///恶魔法杖
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_STAFF_CITRONSTAFF,1,false);                ///枸木法杖
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_STAFF_CLOUDSTAFF,1,false);                 ///流云法杖
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_STAFF_MONKSTAFF,1,false);                  ///武僧之杖
    //PIT_STAFF_END
    
    //PIT_STAFF_PRO_BEGIN
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_STAFF_PRO_OAKSTAFF, 1,false);                  ///绿玉 Emerald
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_STAFF_PRO_FIRSTAFF,1,false);                   ///启明星 Venus
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_STAFF_PRO_ASHESSTAFF, 1,false);                ///地狱之吻 Cerebus' Bite
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_STAFF_PRO_DEMONSTAFF, 1,false);                ///招魂者 Exorcist
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_STAFF_PRO_CITRONSTAFF, 1,false);               ///英普瑞斯之矛 The Prius Spear
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_STAFF_PRO_CLOUDSTAFF,1,false);                 ///鲜血勇气 Blood courage
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_STAFF_PRO_MONKSTAFF,1,false);                  ///大天使 Archangel
    //PIT_STAFF_PRO_END
    
    //PIT_SHIELD_BEGIN
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SHIELD_WOODENSHIELD,1,false);               ///圆木盾
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SHIELD_TRIANGLESHIELD,1,false);             ///三角盾
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SHIELD_STEELSHIELD,1,false);                ///精钢盾
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SHIELD_EAGLESHIELD,1,false);                ///鹰盾
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SHIELD_OSTEOSCUTE,1,false);                 ///骨盾
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SHIELD_GOLDENSHIELD,1,false);               ///黄金盾
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SHIELD_TOWERSHIELD,1,false);                ///塔盾
    //PIT_SHIELD_END
    
    //PIT_SHIELD_PRO_BEGIN
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SHIELD_PRO_WOODENSHIELD,1,false);               ///黑暗防御者 Dark defender
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SHIELD_PRO_TRIANGLESHIELD,1,false);             ///鬼脸 Grimace
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SHIELD_PRO_STEELSHIELD,1,false);                ///守夜人 The night watchman
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SHIELD_PRO_EAGLESHIELD,1,false);                ///绿魔 Green Goblin
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SHIELD_PRO_OSTEOSCUTE,1,false);                 ///骷髅王的身躯 Skeleton King's body
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SHIELD_PRO_GOLDENSHIELD,1,false);               ///美杜莎的镜子Medusa mirror
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SHIELD_PRO_TOWERSHIELD,1,false);                ///叹息之墙 Wall of sighs
    //PIT_SHIELD_PRO_END
    
    //PIT_CLOTH_BEGIN
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_CLOTH_SHOES,1,false);                    ///皮靴
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_CLOTH_MAGA_CAP,1,false);                 ///法师帽
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_CLOTH_CLOTH,1,false);                    ///布甲
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_CLOTH_LEATHERARMOR,1,false);             ///皮甲
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_CLOTH_CHAINSHOES, 1,false);              ///链靴
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_CLOTH_HELEMT,1,false);                   ///头盔
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_CLOTH_STEELARMOR,1,false);               ///钢甲
    //PIT_CLOTH_END
    
    //PIT_CLOTH_PRO_BEGIN
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_CLOTH_PRO_SHOES,1,false);                    ///旅人之靴 Boots of travel
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_CLOTH_PRO_MAGA_CAP,1,false);                 ///大法师之帽 Grand Master's hat
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_CLOTH_PRO_CLOTH,1,false);                    ///银色月光 Silver moonlight
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_CLOTH_PRO_LEATHERARMOR,1,false);             ///生命牢笼 Life cage
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_CLOTH_PRO_CHAINSHOES,1,false);               ///云之足径 Foot diameter of cloud
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_CLOTH_PRO_HELEMT,1,false);                   ///骑士容貌 Knight looks
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_CLOTH_PRO_STEELARMOR,1,false);               ///寡妇对抗者 No widow
    //PIT_CLOTH_PRO_END
    
    //PIT_ORNAMENT_BEGIN
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_ORNAMENT_RING,1,false);                  ///银戒指
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_ORNAMENT_MEDAL, 1,false);                ///勋章
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_ORNAMENT_SHELLNECKLACE,1,false);         ///贝壳项链
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_ORNAMENT_PENDANT,1,false);               ///吊坠
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_ORNAMENT_NECKLACE,1,false);              ///项链
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_ORNAMENT_SUPERMEDAL,1,false);            ///高级勋章
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_ORNAMENT_JEWELS,1,false);                ///宝石项链
    //PIT_ORNAMENT_END
    
    //PIT_ORNAMENT_PRO_BEGIN
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_ORNAMENT_PRO_RING,1,false);                  ///翠玉指环 Emerald ring
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_ORNAMENT_PRO_MEDAL,1,false);                 ///金色勇气 Golden courage
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_ORNAMENT_PRO_SHELLNECKLACE,1,false);         ///威廉勋章 William Medal
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_ORNAMENT_PRO_PENDANT,1,false);               ///奥妮克希亚之血 Blood of Onyxia
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_ORNAMENT_PRO_NECKLACE, 1,false);             ///圣者遗物  Sacred Relic
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_ORNAMENT_PRO_SUPERMEDAL, 1,false);           ///振奋宝石 Hyperstone
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_ORNAMENT_PRO_JEWELS,1,false);                ///海洋之心 Heart of Ocean
    //PIT_ORNAMENT_END
    
    //PIT_SCROLL_BEGIN
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SCROLL_INDENTIFY, 1,false);                   ////辨识卷轴 Scroll of Identify
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SCROLL_TELEPORT, 1,false);                    ////传送卷轴 Scroll of Random Teleport
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SCROLL_SPEED, 1,false);                       ////速度卷轴 Scroll of Speed
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SCROLL_STEALTH,1,false);                      ////隐身卷轴 Scroll of Stealth
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SCROLL_STRONGER,1,false);                     ////强壮卷轴 Scroll of Stronger
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_SCROLL_DESTINY, 1,false);                     ////命运卷轴 Scroll of Destiny
    //PIT_SCROLL_END
    
    ///PIT_POTION_BEGIN
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_POTION_MINORHEALTH,1,false);                  ///小治疗药水 Minor Health Potion
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_POTION_LESSERHEALTH,1,false);                 ///轻微治疗药水 Lesser Health Potion
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_POTION_HEALTH, 1,false);                      ///治疗药水 Health Potion
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_POTION_MINORMANA,1,false);                    ///小魔法药水 Minor Mana Potion
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_POTION_LESSERMANA,1,false);                   ///轻微魔法药水 Lesser Mana Potion
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_POTION_MANA, 1,false);                        ///魔法药水 Mana Potion
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_POTION_MINORRECOVERY, 1,false);               ///小恢复药水 Minor Recovery Potion
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_POTION_LESSERRECOVERY,1,false);               ///轻微恢复药水 Lesser Recovery Potion
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_POTION_RECOVERY, 1,false);                    ///恢复药水 Recovery Potion
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_POTION_DETOXIFICATION, 1,false);              ///解毒药水 Detoxification Potion
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_POTION_SPECIFIC,1,false);                     ///特效药水 Specific Potion
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_POTION_HEALING, 1,false);                     ///治愈药水 Healing Potion
    PlayerProperty::getInstance()->addItemToBag(PickableItem::PickableItemType::PIT_POTION_UNIVERSAL, 1,false);                   ///万能药水 Universal Potion
    
    
    CCLOG("PlayerProperty::getInstance()->getPlayerBag().size():%lu",PlayerProperty::getInstance()->getPlayerBag().size());
    for (int i =0 ; i<PlayerProperty::getInstance()->getPlayerBag().size(); i++) {
        PickableItem::PickableItemType type = PlayerProperty::getInstance()->getPlayerBag()[i]->getPickableItemType();
        std::string typeName = PICKABLE_ITEM_NAMES[type];
        TextBMFont* textItem =TextBMFont::create(typeName, UtilityHelper::getLocalStringForUi("FONT_NAME"));
        textItem->setTouchEnabled(true);
        textItem->setScale(0.5);
        m_pGridView->pushBackCustomItem(textItem);
    }
    m_pGridView->forceDoLayout();
}

