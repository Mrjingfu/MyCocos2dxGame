//
//  QuestionMark.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/9/22.
//
//

#include "QuestionMark.h"
USING_NS_CC;

QuestionMark::QuestionMark()
{
    m_Type = UIT_QUESTION_MARK;
    m_QMType = QMT_RANDOM;
}
QuestionMark::~QuestionMark()
{
}

bool QuestionMark::loadModel()
{
    bool ret = true;
    m_pSprite = HueSprite::create("frame_yellow.png");
    if(!m_pSprite)
    {
        CCLOG("QuestionMark : Load frame model failed!");
        ret = false;
    }
    m_pSprite->setHue(0.05f*M_PI*2.0f);
    addChild(m_pSprite);
    
    m_pMainSprite = HueSprite::create("question_mark.png");
    if(!m_pMainSprite)
    {
        CCLOG("QuestionMark : Load main model failed!");
        ret = false;
    }
    m_pMainSprite->setScale(0.7f);
    addChild(m_pMainSprite);
    EaseSineOut* scaleTo1 = EaseSineOut::create(ScaleTo::create(0.5f, 0.9f));
    EaseSineIn* scaleTo2 = EaseSineIn::create(ScaleTo::create(0.5f, 0.7f));
    Sequence* sequence = Sequence::create(scaleTo1, scaleTo2, NULL);
    EaseSineIn* rotateBy = EaseSineIn::create(RotateBy::create(1.0f, Vec3(0, 360, 0)));
    Spawn* spawn = Spawn::create(sequence, rotateBy, NULL);
    m_pMainSprite->runAction(RepeatForever::create(spawn));
    return ret;
}
void QuestionMark::onEnter()
{
    UsableItem::onEnter();
    scheduleUpdate();
}
void QuestionMark::onExit()
{
    unscheduleUpdate();
    UsableItem::onExit();
}
void QuestionMark::update(float delta)
{
    if(m_pMainSprite && m_QMType == QMT_RANDOM)
        m_pMainSprite->setHue(m_pMainSprite->getHue()+delta*2);
}
void QuestionMark::setQuestionMarkType(QUESTION_MARK_TYPE type)
{
    m_QMType = type;
    if(m_pMainSprite && m_QMType != QMT_RANDOM)
        m_pMainSprite->setHue(0.2f*m_QMType*M_PI*2);
}