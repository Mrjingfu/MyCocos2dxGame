//
//  ExcalmationMark.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/9/22.
//
//

#include "ExcalmationMark.h"
USING_NS_CC;

ExcalmationMark::ExcalmationMark()
{
    m_Type = SIT_EXCALMATION_MARK;
}
ExcalmationMark::~ExcalmationMark()
{
}

bool ExcalmationMark::loadModel()
{
    bool ret = true;
    m_pSprite = HueSprite::create("frame_yellow.png");
    if(!m_pSprite)
    {
        CCLOG("ExcalmationMark : Load frame model failed!");
        ret = false;
    }
    m_pSprite->setHue(0.05f*M_PI*2.0f);
    addChild(m_pSprite);

    m_pMainSprite = HueSprite::create("exclamation_mark.png");
    if(!m_pMainSprite)
    {
        CCLOG("ExcalmationMark : Load main model failed!");
        ret = false;
    }
    m_pMainSprite->setHue(0.2f*M_PI*2.0f);
    m_pMainSprite->setScale(0.7f);
    addChild(m_pMainSprite);
    EaseSineOut* scaleTo1 = EaseSineOut::create(ScaleTo::create(0.5f, 0.9f));
    EaseSineIn* scaleTo2 = EaseSineIn::create(ScaleTo::create(0.5f, 0.7f));
    Sequence* sequence = Sequence::create(scaleTo1, scaleTo2, NULL);
    m_pMainSprite->runAction(RepeatForever::create(sequence));
    return ret;
}