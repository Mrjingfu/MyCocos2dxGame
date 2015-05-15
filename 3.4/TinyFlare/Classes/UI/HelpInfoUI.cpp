//
//  HelpInfoUI.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/5/14.
//
//

#include "HelpInfoUI.h"
#include "SimpleAudioEngine.h"
#include "UtilityHelper.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;
HelpInfoUI* HelpInfoUI::create()
{
    HelpInfoUI *pRet = new(std::nothrow) HelpInfoUI();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}
HelpInfoUI::HelpInfoUI()
{
    m_pPreviousBtn  = nullptr;
    m_pNextBtn      = nullptr;
    m_pExitBtn      = nullptr;
    m_pTableView    = nullptr;
    m_nCurrentPage  = 0;
}
HelpInfoUI::~HelpInfoUI()
{
}
bool HelpInfoUI::init()
{
    auto keyboardListener=EventListenerKeyboard::create();
    keyboardListener->onKeyReleased=CC_CALLBACK_2(HelpInfoUI::onKeyReleased,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,this);
    
    cocos2d::Size size = Director::getInstance()->getVisibleSize();
    float scale = size.height/640.0f;
    
    ParticleSystemQuad* starfield= ParticleSystemQuad::create("starfield.plist");
    if(!starfield)
    {
        CCLOG("Load explosion particle system failed! file: starfield.plist");
        return nullptr;
    }
    this->addChild(starfield);
    
    m_pTableView = TableView::create(this, size);
    m_pTableView->setDirection(ScrollView::Direction::HORIZONTAL);
    m_pTableView->setBounceable(true);
    m_pTableView->setTouchEnabled(false);
    m_pTableView->setDelegate(this);
    this->addChild(m_pTableView);
    
    m_pPreviousBtn = ui::Button::create("left.png");
    m_pPreviousBtn->addTouchEventListener(CC_CALLBACK_2(HelpInfoUI::pressPreviousBtn, this));
    m_pPreviousBtn->setPosition(Vec2(size.width*0.8f, size.height*0.1f));
    m_pPreviousBtn->setScale(0.5f);
    m_pPreviousBtn->setScale(0);
    this->addChild(m_pPreviousBtn);
    
    m_pNextBtn = ui::Button::create("right.png");
    m_pNextBtn->addTouchEventListener(CC_CALLBACK_2(HelpInfoUI::pressNextBtn, this));
    m_pNextBtn->setPosition(Vec2(size.width*0.9f, size.height*0.1f));
    m_pNextBtn->setScale(0.5f);
    this->addChild(m_pNextBtn);
    
    m_pExitBtn = ui::Button::create("exit.png");
    m_pExitBtn->addTouchEventListener(CC_CALLBACK_2(HelpInfoUI::pressExitBtn, this));
    m_pExitBtn->setPosition(Vec2(size.width - 50.0f*scale, size.height - 50.0f*scale));
    m_pExitBtn->setScale(0.5f);
    this->addChild(m_pExitBtn);
    
    m_pTableView->reloadData();
    
    return true;
}

cocos2d::Size HelpInfoUI::cellSizeForTable(cocos2d::extension::TableView *table)
{
    return Director::getInstance()->getVisibleSize();
}
cocos2d::extension::TableViewCell* HelpInfoUI::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    CCLOG("%zd",idx);
    cocos2d::Size size = Director::getInstance()->getVisibleSize();
    TableViewCell *cell = table->cellAtIndex(idx);
    if (!cell) {
        cell = TableViewCell::create();
        cell->setCascadeColorEnabled(true);
        switch (idx) {
            case 0:
                {
                    cocos2d::ui::Text* desc = ui::Text::create(UtilityHelper::getLocalString("CONTROL_DESC"), "FZXS12.TTF", size.height*0.08f);
                    desc->setColor(Color3B(208,255,208));
                    desc->setPosition(Vec2(size.width*0.5f, size.height*0.9f));
                    cell->addChild(desc);
                    
                    cocos2d::Sprite* joystickLeftBg = Sprite::create("joystick_bg1.png");
                    joystickLeftBg->setPosition(size.width*0.2f, size.height*0.65f);
                    joystickLeftBg->setScale(0.8f);
                    cell->addChild(joystickLeftBg);
                    
                    cocos2d::Sprite* joystickLeft = Sprite::create("joystick1.png");
                    joystickLeft->setPosition(size.width*0.2f, size.height*0.65f);
                    joystickLeft->setScale(0.8f);
                    cell->addChild(joystickLeft);
                    
                    Label* leftDesc = Label::createWithTTF(UtilityHelper::getLocalString("JOYSTICK_LEFT_DESC"), "FZXS12.TTF", size.height*0.04f);
                    leftDesc->setPosition(size.width*0.6f, size.height*0.65f);
                    leftDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    leftDesc->setDimensions(size.width*0.5f, size.height*0.2f);
                    leftDesc->setColor(Color3B(208,255,208));
                    cell->addChild(leftDesc);
                    
                    cocos2d::Sprite* joystickRightBg = Sprite::create("joystick_bg2.png");
                    joystickRightBg->setPosition(size.width*0.2f, size.height*0.35f);
                    joystickRightBg->setScale(0.8f);
                    cell->addChild(joystickRightBg);
                    
                    Label* rightDesc = Label::createWithTTF(UtilityHelper::getLocalString("JOYSTICK_RIGHT_DESC"), "FZXS12.TTF", size.height*0.04f);
                    rightDesc->setPosition(size.width*0.6f, size.height*0.35f);
                    rightDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    rightDesc->setDimensions(size.width*0.5f, size.height*0.2f);
                    rightDesc->setColor(Color3B(208,255,208));
                    cell->addChild(rightDesc);
                    
                    cocos2d::Sprite* joystickRight = Sprite::create("joystick1.png");
                    joystickRight->setPosition(size.width*0.2f, size.height*0.35f);
                    joystickRight->setScale(0.8f);
                    cell->addChild(joystickRight);
                }
                break;
            case 1:
                {
                    cocos2d::ui::Text* desc = ui::Text::create(UtilityHelper::getLocalString("ITEM_DESC"), "FZXS12.TTF", size.height*0.08f);
                    desc->setColor(Color3B(208,255,208));
                    desc->setPosition(Vec2(size.width*0.5f, size.height*0.9f));
                    cell->addChild(desc);
                    
                    Node* accelIcon = Node::create();
                    auto bound = ui::ImageView::create("bound.png");
                    auto accel = ui::ImageView::create("accel.png");
                    accelIcon->addChild(bound);
                    accelIcon->addChild(accel);
                    accelIcon->setPosition(size.width*0.2f, size.height*0.76f);
                    accelIcon->setScale(0.5f);
                    cell->addChild(accelIcon);
                    
                    Label* accelDesc = Label::createWithTTF(UtilityHelper::getLocalString("ACCEL_DESC"), "FZXS12.TTF", size.height*0.04f);
                    accelDesc->setPosition(size.width*0.6f, size.height*0.76f);
                    accelDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    accelDesc->setDimensions(size.width*0.6f, size.height*0.08f);
                    accelDesc->setColor(Color3B(208,255,208));
                    cell->addChild(accelDesc);
                    
                    Node* multiIcon = Node::create();
                    bound = ui::ImageView::create("bound.png");
                    auto multi = ui::ImageView::create("multi.png");
                    multiIcon->addChild(bound);
                    multiIcon->addChild(multi);
                    multiIcon->setPosition(size.width*0.2f, size.height*0.62f);
                    multiIcon->setScale(0.5f);
                    cell->addChild(multiIcon);
                    
                    Label* multiDesc = Label::createWithTTF(UtilityHelper::getLocalString("MULTI_DESC"), "FZXS12.TTF", size.height*0.04f);
                    multiDesc->setPosition(size.width*0.6f, size.height*0.62f);
                    multiDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    multiDesc->setDimensions(size.width*0.6f, size.height*0.08f);
                    multiDesc->setColor(Color3B(208,255,208));
                    cell->addChild(multiDesc);
                    
                    Node* protectedIcon = Node::create();
                    bound = ui::ImageView::create("bound.png");
                    auto pprotected = ui::ImageView::create("protected.png");
                    protectedIcon->addChild(bound);
                    protectedIcon->addChild(pprotected);
                    protectedIcon->setPosition(size.width*0.2f, size.height*0.48f);
                    protectedIcon->setScale(0.5f);
                    cell->addChild(protectedIcon);
                    
                    Label* protectedDesc = Label::createWithTTF(UtilityHelper::getLocalString("PROTECTED_DESC"), "FZXS12.TTF", size.height*0.04f);
                    protectedDesc->setPosition(size.width*0.6f, size.height*0.48f);
                    protectedDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    protectedDesc->setDimensions(size.width*0.6f, size.height*0.08f);
                    protectedDesc->setColor(Color3B(208,255,208));
                    cell->addChild(protectedDesc);
                    
                    Node* timeIcon = Node::create();
                    bound = ui::ImageView::create("bound.png");
                    auto time = ui::ImageView::create("time.png");
                    timeIcon->addChild(bound);
                    timeIcon->addChild(time);
                    timeIcon->setPosition(size.width*0.2f, size.height*0.34f);
                    timeIcon->setScale(0.5f);
                    cell->addChild(timeIcon);
                    
                    Label* timeDesc = Label::createWithTTF(UtilityHelper::getLocalString("TIME_DESC"), "FZXS12.TTF", size.height*0.04f);
                    timeDesc->setPosition(size.width*0.6f, size.height*0.34f);
                    timeDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    timeDesc->setDimensions(size.width*0.6f, size.height*0.08f);
                    timeDesc->setColor(Color3B(208,255,208));
                    cell->addChild(timeDesc);
                    
                    Node* boomIcon = Node::create();
                    bound = ui::ImageView::create("bound.png");
                    auto boom = ui::ImageView::create("boom.png");
                    boomIcon->addChild(bound);
                    boomIcon->addChild(boom);
                    boomIcon->setPosition(size.width*0.2f, size.height*0.2f);
                    boomIcon->setScale(0.5f);
                    cell->addChild(boomIcon);
                    
                    Label* boomDesc = Label::createWithTTF(UtilityHelper::getLocalString("BOOM_DESC"), "FZXS12.TTF", size.height*0.04f);
                    boomDesc->setPosition(size.width*0.6f, size.height*0.2f);
                    boomDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    boomDesc->setDimensions(size.width*0.6f, size.height*0.08f);
                    boomDesc->setColor(Color3B(208,255,208));
                    cell->addChild(boomDesc);

                }
                break;
            case 2:
                {
                    cocos2d::ui::Text* desc = ui::Text::create(UtilityHelper::getLocalString("ENEMY_DESC"), "FZXS12.TTF", size.height*0.08f);
                    desc->setColor(Color3B(208,255,208));
                    desc->setPosition(Vec2(size.width*0.5f, size.height*0.9f));
                    cell->addChild(desc);
                    
                    cocos2d::Sprite* circle = Sprite::create("circle.png");
                    circle->setPosition(size.width*0.2f, size.height*0.75f);
                    circle->setScale(0.8f);
                    cell->addChild(circle);
                    
                    Label* circleDesc = Label::createWithTTF(UtilityHelper::getLocalString("CIRCLE_DESC"), "FZXS12.TTF", size.height*0.04f);
                    circleDesc->setPosition(size.width*0.6f, size.height*0.75f);
                    circleDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    circleDesc->setDimensions(size.width*0.6f, size.height*0.08f);
                    circleDesc->setColor(Color3B(208,255,208));
                    cell->addChild(circleDesc);
                    
                    ParticleSystemQuad* colorCircle = ParticleSystemQuad::create("colorgeometry.plist");
                    colorCircle->setPositionType(ParticleSystem::PositionType::RELATIVE);
                    colorCircle->setPosition(size.width*0.2f, size.height*0.65f);
                    colorCircle->setScale(0.6f);
                    Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("circle.png");
                    colorCircle->setTexture(texture);
                    colorCircle->setAutoRemoveOnFinish(true);
                    cell->addChild(colorCircle);
                    
                    Label* colorCircleDesc = Label::createWithTTF(UtilityHelper::getLocalString("COLOR_CIRCLE_DESC"), "FZXS12.TTF", size.height*0.04f);
                    colorCircleDesc->setPosition(size.width*0.6f, size.height*0.6f);
                    colorCircleDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    colorCircleDesc->setDimensions(size.width*0.6f, size.height*0.2f);
                    colorCircleDesc->setColor(Color3B(208,255,208));
                    cell->addChild(colorCircleDesc);
                    
                    cocos2d::Sprite* triangle = Sprite::create("triangle.png");
                    triangle->setPosition(size.width*0.2f, size.height*0.45f);
                    triangle->setScale(0.8f);
                    triangle->setColor(Color3B(253,255,12));
                    cell->addChild(triangle);
                    ScaleTo* scaleTo1 = ScaleBy::create(0.2f, 0.8f);
                    ScaleTo* scaleTo2 = ScaleBy::create(0.2f, 1.25f);
                    Sequence* sequence = Sequence::createWithTwoActions(scaleTo1, scaleTo2);
                    RepeatForever* repeatForever = RepeatForever::create(sequence);
                    triangle->runAction(repeatForever);
                    
                    Label* triangleDesc = Label::createWithTTF(UtilityHelper::getLocalString("TRIANGLE_DESC"), "FZXS12.TTF", size.height*0.04f);
                    triangleDesc->setPosition(size.width*0.6f, size.height*0.40f);
                    triangleDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    triangleDesc->setDimensions(size.width*0.6f, size.height*0.2f);
                    triangleDesc->setColor(Color3B(208,255,208));
                    cell->addChild(triangleDesc);
                    
                    ParticleSystemQuad* colorTriangle = ParticleSystemQuad::create("colorgeometry.plist");
                    colorTriangle->setPositionType(ParticleSystem::PositionType::RELATIVE);
                    colorTriangle->setPosition(size.width*0.2f, size.height*0.25f);
                    colorTriangle->setScale(0.6f);
                    colorTriangle->setColor(Color3B(253,255,12));
                    texture = Director::getInstance()->getTextureCache()->addImage("triangle.png");
                    colorTriangle->setTexture(texture);
                    colorTriangle->setAutoRemoveOnFinish(true);
                    cell->addChild(colorTriangle);
                    scaleTo1 = ScaleBy::create(0.2f, 0.8f);
                    scaleTo2 = ScaleBy::create(0.2f, 1.25f);
                    sequence = Sequence::createWithTwoActions(scaleTo1, scaleTo2);
                    repeatForever = RepeatForever::create(sequence);
                    colorTriangle->runAction(repeatForever);
                    
                    Label* colorTriangleDesc = Label::createWithTTF(UtilityHelper::getLocalString("COLOR_TRIANGLE_DESC"), "FZXS12.TTF", size.height*0.04f);
                    colorTriangleDesc->setPosition(size.width*0.6f, size.height*0.25f);
                    colorTriangleDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    colorTriangleDesc->setDimensions(size.width*0.6f, size.height*0.1f);
                    colorTriangleDesc->setColor(Color3B(208,255,208));
                    cell->addChild(colorTriangleDesc);
                }
                break;
            case 3:
                {
                    cocos2d::ui::Text* desc = ui::Text::create(UtilityHelper::getLocalString("ENEMY_DESC"), "FZXS12.TTF", size.height*0.08f);
                    desc->setColor(Color3B(208,255,208));
                    desc->setPosition(Vec2(size.width*0.5f, size.height*0.9f));
                    cell->addChild(desc);
                
                    cocos2d::Sprite* diamond = Sprite::create("diamond.png");
                    diamond->setPosition(size.width*0.2f, size.height*0.75f);
                    diamond->setScale(0.8f);
                    diamond->setColor(Color3B(64,255,1));
                    cell->addChild(diamond);
                    ScaleTo* scaleTo1 = ScaleBy::create(0.5f, 0.5f, 1.0f);
                    ScaleTo* scaleTo2 = ScaleBy::create(0.5f, 2.0f, 1.0f);
                    Sequence* sequence = Sequence::createWithTwoActions(scaleTo1, scaleTo2);
                    RepeatForever* repeatForever = RepeatForever::create(sequence);
                    diamond->runAction(repeatForever);
                    
                    Label* diamondDesc = Label::createWithTTF(UtilityHelper::getLocalString("DIAMOND_DESC"), "FZXS12.TTF", size.height*0.04f);
                    diamondDesc->setPosition(size.width*0.6f, size.height*0.75f);
                    diamondDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    diamondDesc->setDimensions(size.width*0.6f, size.height*0.08f);
                    diamondDesc->setColor(Color3B(208,255,208));
                    cell->addChild(diamondDesc);
                    
                    ParticleSystemQuad* colorDiamond = ParticleSystemQuad::create("colorgeometry.plist");
                    colorDiamond->setPositionType(ParticleSystem::PositionType::RELATIVE);
                    colorDiamond->setPosition(size.width*0.2f, size.height*0.6f);
                    colorDiamond->setScale(0.6f);
                    Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("diamond.png");
                    colorDiamond->setTexture(texture);
                    colorDiamond->setAutoRemoveOnFinish(true);
                    colorDiamond->setColor(Color3B(64,255,1));
                    cell->addChild(colorDiamond);
                    scaleTo1 = ScaleBy::create(0.5f, 0.5f, 1.0f);
                    scaleTo2 = ScaleBy::create(0.5f, 2.0f, 1.0f);
                    sequence = Sequence::createWithTwoActions(scaleTo1, scaleTo2);
                    repeatForever = RepeatForever::create(sequence);
                    colorDiamond->runAction(repeatForever);
                    
                    Label* colorDiamondDesc = Label::createWithTTF(UtilityHelper::getLocalString("COLOR_DIAMOND_DESC"), "FZXS12.TTF", size.height*0.04f);
                    colorDiamondDesc->setPosition(size.width*0.6f, size.height*0.55f);
                    colorDiamondDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    colorDiamondDesc->setDimensions(size.width*0.6f, size.height*0.2f);
                    colorDiamondDesc->setColor(Color3B(208,255,208));
                    cell->addChild(colorDiamondDesc);
                    
                    cocos2d::Sprite* star = Sprite::create("star.png");
                    star->setPosition(size.width*0.2f, size.height*0.45f);
                    star->setScale(0.8f);
                    star->setColor(Color3B(0,224,252));
                    cell->addChild(star);
                    RotateBy* rotateBy = RotateBy::create(1.0f, 90);
                    repeatForever = RepeatForever::create(rotateBy);
                    star->runAction(repeatForever);
                    
                    Label* starDesc = Label::createWithTTF(UtilityHelper::getLocalString("STAR_DESC"), "FZXS12.TTF", size.height*0.04f);
                    starDesc->setPosition(size.width*0.6f, size.height*0.40f);
                    starDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    starDesc->setDimensions(size.width*0.6f, size.height*0.2f);
                    starDesc->setColor(Color3B(208,255,208));
                    cell->addChild(starDesc);
                    
                    ParticleSystemQuad* colorStar = ParticleSystemQuad::create("colorgeometry.plist");
                    colorStar->setPositionType(ParticleSystem::PositionType::RELATIVE);
                    colorStar->setPosition(size.width*0.2f, size.height*0.25f);
                    colorStar->setScale(0.6f);
                    colorStar->setColor(Color3B(0,224,252));
                    texture = Director::getInstance()->getTextureCache()->addImage("star.png");
                    colorStar->setTexture(texture);
                    colorStar->setAutoRemoveOnFinish(true);
                    cell->addChild(colorStar);
                    rotateBy = RotateBy::create(1.0f, 90);
                    repeatForever = RepeatForever::create(rotateBy);
                    colorStar->runAction(repeatForever);
                    
                    Label* colorStarDesc = Label::createWithTTF(UtilityHelper::getLocalString("COLOR_STAR_DESC"), "FZXS12.TTF", size.height*0.04f);
                    colorStarDesc->setPosition(size.width*0.6f, size.height*0.25f);
                    colorStarDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    colorStarDesc->setDimensions(size.width*0.6f, size.height*0.1f);
                    colorStarDesc->setColor(Color3B(208,255,208));
                    cell->addChild(colorStarDesc);
                }
                break;
            case 4:
                {
                    cocos2d::ui::Text* desc = ui::Text::create(UtilityHelper::getLocalString("ENEMY_DESC"), "FZXS12.TTF", size.height*0.08f);
                    desc->setColor(Color3B(208,255,208));
                    desc->setPosition(Vec2(size.width*0.5f, size.height*0.9f));
                    cell->addChild(desc);
                
                    cocos2d::Sprite* hexagon = Sprite::create("hexagon.png");
                    hexagon->setPosition(size.width*0.2f, size.height*0.75f);
                    hexagon->setScale(0.8f);
                    hexagon->setColor(Color3B(64,255,1));
                    cell->addChild(hexagon);
                    RotateBy* rotateBy = RotateBy::create(1.0f, -180);
                    RepeatForever* repeatForever = RepeatForever::create(rotateBy);
                    hexagon->runAction(repeatForever);
                    
                    Label* hexagonDesc = Label::createWithTTF(UtilityHelper::getLocalString("HEXAGON_DESC"), "FZXS12.TTF", size.height*0.04f);
                    hexagonDesc->setPosition(size.width*0.6f, size.height*0.75f);
                    hexagonDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    hexagonDesc->setDimensions(size.width*0.6f, size.height*0.08f);
                    hexagonDesc->setColor(Color3B(208,255,208));
                    cell->addChild(hexagonDesc);
                    
                    ParticleSystemQuad* colorHexagon = ParticleSystemQuad::create("colorgeometry.plist");
                    colorHexagon->setPositionType(ParticleSystem::PositionType::RELATIVE);
                    colorHexagon->setPosition(size.width*0.2f, size.height*0.6f);
                    colorHexagon->setScale(0.6f);
                    Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("hexagon.png");
                    colorHexagon->setTexture(texture);
                    colorHexagon->setAutoRemoveOnFinish(true);
                    colorHexagon->setColor(Color3B(64,255,1));
                    cell->addChild(colorHexagon);
                    rotateBy = RotateBy::create(1.0f, -180);
                    repeatForever = RepeatForever::create(rotateBy);
                    colorHexagon->runAction(repeatForever);
                    
                    Label* colorHexagonDesc = Label::createWithTTF(UtilityHelper::getLocalString("COLOR_HEXAGON_DESC"), "FZXS12.TTF", size.height*0.04f);
                    colorHexagonDesc->setPosition(size.width*0.6f, size.height*0.55f);
                    colorHexagonDesc->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::TOP);
                    colorHexagonDesc->setDimensions(size.width*0.6f, size.height*0.2f);
                    colorHexagonDesc->setColor(Color3B(208,255,208));
                    cell->addChild(colorHexagonDesc);
                }
                break;
            default:
                break;
        }
        
    }
    
    return cell;
}
ssize_t HelpInfoUI::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return 5;
}

void HelpInfoUI::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
}

void HelpInfoUI::pressPreviousBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        cocos2d::Size size = Director::getInstance()->getVisibleSize();
        m_nCurrentPage--;
        m_pTableView->setContentOffsetInDuration(Vec2(-size.width*m_nCurrentPage,0),0.1f);
        if(m_nCurrentPage == 0)
        {
            m_pNextBtn->setScale(0.5f);
            m_pPreviousBtn->setScale(0);
        }
        else
        {
            m_pNextBtn->setScale(0.5f);
            m_pPreviousBtn->setScale(0.5f);
        }
    }
}
void HelpInfoUI::pressNextBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        cocos2d::Size size = Director::getInstance()->getVisibleSize();
        m_nCurrentPage++;
        m_pTableView->setContentOffsetInDuration(Vec2(-size.width*m_nCurrentPage,0),0.1f);
        if(m_nCurrentPage == 4)
        {
            m_pNextBtn->setScale(0);
            m_pPreviousBtn->setScale(0.5f);
        }
        else
        {
            m_pNextBtn->setScale(0.5f);
            m_pPreviousBtn->setScale(0.5f);
        }
    }
}
void HelpInfoUI::pressExitBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        Director::getInstance()->popScene();
    }
}
void HelpInfoUI::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        Director::getInstance()->popScene();
    }
}