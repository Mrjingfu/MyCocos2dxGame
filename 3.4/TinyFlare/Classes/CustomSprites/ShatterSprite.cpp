//
//  ShatterSprite.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/4/14.
//
//

#include "ShatterSprite.h"
USING_NS_CC;

FragSprite::FragSprite()
{
    m_nRandomNumber = -1;
}
FragSprite* FragSprite::create()
{
    
    FragSprite* ret = new (std::nothrow) FragSprite();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;

}
ShatterSprite* ShatterSprite::create(const std::string& texFileName)
{
    ShatterSprite* ret = new (std::nothrow) ShatterSprite();
    if (ret && ret->init(texFileName))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool ShatterSprite::init(const std::string& texFileName)
{
    bool ret = Sprite::initWithFile(texFileName.c_str());
    createShatter();
    return ret;
}

void ShatterSprite::createShatter()
{
    cocos2d::Size contentSize = getContentSize();
    const int nRow= (int) floorf(contentSize.height / m_fGridSideLen);
    const int nCol= (int) floorf(contentSize.width / m_fGridSideLen);
    const int fragCount = nRow * nCol;
    
    m_pFragBatchNode = SpriteBatchNode::createWithTexture(this->getTexture(), fragCount);
    addChild(m_pFragBatchNode);
    m_pFragBatchNode->setVisible(false);
 
    m_GridSprite.resize(nRow);
    for(int i = 0; i < nRow; i++)
        m_GridSprite[i].resize(nCol);
    
    for(int i = 0; i < nRow; i++){
        for(int j = 0; j < nCol; j++){
            FragSprite* frag = FragSprite::create();
            if(frag)
            {
                frag->initWithTexture(this->getTexture());
                m_GridSprite[i][j]=frag;
                m_pFragBatchNode->addChild(frag);
                frag->m_nRandomNumber = cocos2d::random();
            }
        }
    }

}
void ShatterSprite::resetShatter()
{
    cocos2d::Size contentSize= getContentSize();
    int nRow = (int)m_GridSprite.size();
    int nCol = ( nRow == 0 ? 0 : (int)m_GridSprite[0].size());
    const float halfGridSideLen= 0.5f * m_fGridSideLen;
    for(int i = 0; i < nRow; i++){
        for(int j = 0; j < nCol; j++){
            FragSprite* frag = m_GridSprite[i][j];
            float x = j * m_fGridSideLen + halfGridSideLen;
            float y = contentSize.height - (i * m_fGridSideLen + halfGridSideLen);
            frag->setTextureRect(cocos2d::Rect(x - halfGridSideLen,(contentSize.height - y) - halfGridSideLen, m_fGridSideLen,m_fGridSideLen));
            frag->setPosition(x,y);
            frag->setScale(m_fInitalFrageScale);
            frag->setOpacity(255);
            frag->setVisible(true);
        }
    }
}
void ShatterSprite::updateShatterAction(float time, float delta,float growSpeedOfTargetR)
{
    cocos2d::Size contentSize = getContentSize();
    Vec2 center = Vec2(contentSize.width*0.5f, contentSize.height*0.5f);
    float initalTargetR = center.length();
    int nRow = (int)m_GridSprite.size();
    int nCol = ( nRow == 0 ? 0 : (int)m_GridSprite[0].size());
    for(int i = 0; i < nRow; i++){
        for(int j = 0;j < nCol;j++){
            FragSprite* frag = m_GridSprite[i][j];
            if(frag->getOpacity() == 0 || frag->getScale() == 0){
                frag->setVisible(false);
                continue;
            }
            float targetR = initalTargetR + time * growSpeedOfTargetR;
            Vec2 fragPos=frag->getPosition();
            float disToCenter = (fragPos-center).length();
            Vec2 dir;
            if(disToCenter == 0)
                dir = Vec2::ZERO;
            else
            {
                dir = fragPos - center;
                dir.x /= disToCenter;
                dir.y /= disToCenter;
            }
            float disToEdge = targetR - disToCenter;
            float disToEdgeWithRandom = disToEdge+frag->m_nRandomNumber%(int)initalTargetR-initalTargetR/2;
            float movLen= disToEdgeWithRandom*0.0333;
            Vec2 movVec = dir * movLen;
            frag->setPosition(fragPos+movVec);

            float opacity = MAX(0,255 - 255 * disToCenter/initalTargetR);
            frag->setOpacity(opacity);
            frag->setScale(MAX(0,m_fInitalFrageScale - m_fInitalFrageScale*disToCenter/initalTargetR));
        }
    }

}