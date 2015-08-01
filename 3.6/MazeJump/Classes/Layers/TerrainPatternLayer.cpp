//
//  TerrainPatternLayer.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/23.
//
//

#include "TerrainPatternLayer.h"
#include "RunController.h"
#include "PatternsManager.h"
#include "UtilityHelper.h"
#include "AlisaMethod.h"
#include "OutlineEffect3D.h"
#include "GameConst.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;
TerrainPatternLayer* TerrainPatternLayer::create(int index, bool generateCheckPoint)
{
    TerrainPatternLayer *pRet = new(std::nothrow) TerrainPatternLayer();
    if (pRet && pRet->init(index, generateCheckPoint))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}
TerrainPatternLayer::TerrainPatternLayer()
{
    m_fadeInType = FIT_NONE;
}

bool TerrainPatternLayer::init(int index, bool generateCheckPoint)
{
    if ( !Layer::init() )
        return false;
    m_nIndex = index;
    m_patternType = PatternType(PatternsManager::getInstance()->getPatternType(index));
    m_fadeInType = FadeInType(PatternsManager::getInstance()->getPatternFadeInType(index));
    ValueVector terrainCells = PatternsManager::getInstance()->getPatternTerrainCells(index);
    for (Value value : terrainCells) {
        ValueMap cellMap = value.asValueMap();
        std::string modelName = cellMap.at("ModelName").asString();
        int cellType = cellMap.at("CellType").asInt();
        float posX = cellMap.at("PosX").asFloat();
        float posY = cellMap.at("PosY").asFloat();
        float posZ = cellMap.at("PosZ").asFloat();
        float rotX = cellMap.at("RotX").asFloat();
        float rotY = cellMap.at("RotY").asFloat();
        float rotZ = cellMap.at("RotZ").asFloat();
        float scaleX = cellMap.at("ScaleX").asFloat();
        float scaleY = cellMap.at("ScaleY").asFloat();
        float scaleZ = cellMap.at("ScaleZ").asFloat();
        TerrainCell* cell = TerrainCell::create(modelName + ".c3b");
        if(!cell)
            return false;
        cell->setType(TerrainCell::CellType(cellType));
        cell->setCascadeOpacityEnabled(true);
        addChild(cell);
        m_TerrainCellList.pushBack(cell);
        
        switch (m_fadeInType) {
            case FIT_NONE:
                {
                    cell->setPosition3D(Vec3(posX, posY, posZ));
                    cell->setRotation3D(Vec3(rotX, rotY, rotZ));
                    cell->setScaleX(scaleX);
                    cell->setScaleY(scaleY);
                    cell->setScaleZ(scaleZ);
                }
                break;
            case FIT_RANDOM_UP:
                {
                    Color3B randomColor = UtilityHelper::randomColor();
                    cell->setColor(randomColor);
                    cell->setPosition3D(Vec3(posX, -50, posZ));
                    cell->setRotation3D(Vec3(rotX, rotY, rotZ));
                    cell->setScale(0);
                    cell->setScaleY(0);
                    cell->setScaleZ(0);
                    cell->setOpacity(0);
                    float time = cocos2d::random(1.0f, 1.5f);
                    EaseBackInOut* moveTo = EaseBackInOut::create(MoveTo::create(time, Vec3(posX, posY, posZ)));
                    EaseSineIn* scaleTo = EaseSineIn::create(ScaleTo::create(0.5f, 0.985f));
                    EaseSineIn* fadeIn = EaseSineIn::create(FadeIn::create(0.5f));
                    Spawn* spawn = Spawn::create(moveTo, scaleTo, fadeIn, NULL);
                    cell->runAction(spawn);
                    if(cell->getType() == TerrainCell::CT_NORMAL_PLATFORM)
                        generateDecorator(cell, index);
                }
                break;
                
            default:
                break;
        }
    }
    if(m_patternType == PT_CHECKPOINT && generateCheckPoint)
        generateCheckPointDecorator();
    
    return true;
}
void TerrainPatternLayer::update(float delta)
{
    for (int i = 0; i<m_DecoratorList.size(); ++i) {
        Decorator* decorator = m_DecoratorList.at(i);
        if(decorator)
        {
            bool isVisible = RunController::getInstance()->getMainCamera()->isVisibleInFrustum(&decorator->getAABB());
            if(!isVisible)
            {
                eraseDecorator(decorator);
                continue;
            }
            decorator->update(delta);
        }
    }
    
    for (int i = 0; i<m_TerrainCellList.size(); ++i) {
        TerrainCell* cell = m_TerrainCellList.at(i);
        if(cell)
        {
            bool isVisible = RunController::getInstance()->getMainCamera()->isVisibleInFrustum(&cell->getAABB());
            if(!isVisible)
            {
                m_TerrainCellList.eraseObject(cell);
                if(cell->getReferenceCount() > 0)
                    cell->removeFromParentAndCleanup(true);
                cell = nullptr;
            }
        }
    }
}

void TerrainPatternLayer::reset()
{
    if(m_patternType != PT_CHECKPOINT)
        return;
    for (Decorator* decorator : m_DecoratorList) {
        if(decorator && decorator->getType() == Decorator::DT_PORTAL)
        {
            DelayTime* delay = DelayTime::create(0.5f);
            EaseSineOut* scaleTo = EaseSineOut::create(ScaleTo::create(1.5f, 0));
            EaseSineOut* fadeOut = EaseSineOut::create(FadeOut::create(1.5f));
            Spawn* spawn = Spawn::create(scaleTo, fadeOut, NULL);
            CallFunc* callfunc = CallFunc::create(CC_CALLBACK_0(TerrainPatternLayer::eraseDecorator, this,decorator));
            Sequence* sequence = Sequence::create(delay, spawn, callfunc, NULL);
            decorator->runAction(sequence);
            break;
        }
    }
}
bool TerrainPatternLayer::checkRunnerDrop()
{
    Runner* runner = RunController::getInstance()->getMainPlayer();
    if(!runner || runner->getState() != Runner::RS_IDLE)
        return false;
    bool collision = false;
    for (TerrainCell* cell : m_TerrainCellList) {
        if(cell)
        {
            collision = runner->getModifyAABB().intersects(cell->getAABB());
            if(!collision)
                continue;
            else
            {
                runner->onCollision(cell);
                break;
            }
        }
    }
    return !collision;
}
void TerrainPatternLayer::beginCollapse()
{
    TerrainLayer* layer = RunController::getInstance()->getTerrainLayer();
    if(layer)
    {
        for (TerrainCell* cell : m_TerrainCellList)
        {
            if(cell)
            {
                int row = -cell->getPositionZ()/layer->getCellBaseRadius() + 2;
                float time = cocos2d::random(1.0f, 1.5f);
                DelayTime* delayTime = DelayTime::create(2.5f + row*0.25f);
                EaseSineOut* moveTo = EaseSineOut::create(MoveTo::create(time, Vec3(cell->getPositionX(), -50, cell->getPositionZ())));
                EaseSineIn* rotateBy = EaseSineIn::create(RotateBy::create(time, Vec3(cocos2d::random(90.0f, -90.0f),cocos2d::random(-90.0f, 90.0f),0)));
                EaseSineOut* scaleTo = EaseSineOut::create(ScaleTo::create(time, 0.8f));
                DelayTime* delayTime2 = DelayTime::create(0.5f*time);
                EaseSineOut* fadeOut = EaseSineOut::create(FadeOut::create(0.5f*time));
                Sequence* sequece1 = Sequence::create(delayTime2, fadeOut, NULL);
                Spawn* spawn = Spawn::create(moveTo,rotateBy, scaleTo, sequece1, NULL);
                Sequence* sequence2 = Sequence::create(delayTime, spawn, NULL);
                cell->runAction(sequence2);
            }
        }
    }
}
void TerrainPatternLayer::checkCollisionDecorator()
{
    Runner* runner = RunController::getInstance()->getMainPlayer();
    if(!runner)
        return;
    for (Decorator* decorator : m_DecoratorList) {
        if(decorator && decorator->getNeedToCollision())
        {
            bool collision = runner->getModifyAABB().intersects(decorator->getAABB());
            if(collision)
            {
                decorator->setNeedToCollision(false);
                switch (decorator->getType()) {
                    case Decorator::DT_GOLD:
                        {
                            EaseBackInOut* moveTo = EaseBackInOut::create(MoveTo::create(0.5f, Vec3(decorator->getPositionX(), decorator->getPositionY() + 10, decorator->getPositionZ())));
                            EaseBackInOut* scaleTo = EaseBackInOut::create(ScaleTo::create(0.5f, 0.5f));
                            Spawn* spawn = Spawn::create(moveTo, scaleTo, NULL);
                            CallFunc* callfunc = CallFunc::create(CC_CALLBACK_0(TerrainPatternLayer::eraseDecorator, this,decorator));
                            Sequence* sequece = Sequence::create(spawn, callfunc, NULL);
                            decorator->runAction(sequece);
                            localStorageSetItem(USER_GOLD_NUM, localStorageGetItem(USER_GOLD_NUM) + Value(1).asString());
                        }
                        break;
                    case Decorator::DT_HEART:
                        {
                            EaseBackInOut* moveTo = EaseBackInOut::create(MoveTo::create(0.5f, Vec3(decorator->getPositionX(), decorator->getPositionY() + 10, decorator->getPositionZ())));
                            EaseBackInOut* scaleTo = EaseBackInOut::create(ScaleTo::create(0.5f, 0.6f));
                            Spawn* spawn = Spawn::create(moveTo, scaleTo, NULL);
                            CallFunc* callfunc = CallFunc::create(CC_CALLBACK_0(TerrainPatternLayer::eraseDecorator, this,decorator));
                            Sequence* sequece = Sequence::create(spawn, callfunc, NULL);
                            decorator->runAction(sequece);
                            localStorageSetItem(USER_HEART_NUM, localStorageGetItem(USER_HEART_NUM) + Value(1).asString());
                        }
                        break;
                    case Decorator::DT_GOLD_BIG:
                        {
                            EaseBackInOut* moveTo = EaseBackInOut::create(MoveTo::create(0.5f, Vec3(decorator->getPositionX(), decorator->getPositionY() + 10, decorator->getPositionZ())));
                            EaseBackInOut* scaleTo = EaseBackInOut::create(ScaleTo::create(0.5f, 0.8f));
                            Spawn* spawn = Spawn::create(moveTo, scaleTo, NULL);
                            CallFunc* callfunc = CallFunc::create(CC_CALLBACK_0(TerrainPatternLayer::eraseDecorator, this,decorator));
                            Sequence* sequece = Sequence::create(spawn, callfunc, NULL);
                            decorator->runAction(sequece);
                            localStorageSetItem(USER_GOLD_NUM, localStorageGetItem(USER_GOLD_NUM) + Value(5).asString());
                        }
                        break;
                    case Decorator::DT_PORTAL:
                        {
                            Runner* runner = RunController::getInstance()->getMainPlayer();
                            Camera* mainCamera = RunController::getInstance()->getMainCamera();
                            if(mainCamera && runner)
                            {
                                EaseSineOut* moveTo = EaseSineOut::create(MoveTo::create(300.0f, runner->getPosition3D()));
                                DelayTime* delay = DelayTime::create(0.5);
                                CallFunc* callback = CallFunc::create(CC_CALLBACK_0(RunController::switchToMazeJump, RunController::getInstance()));
                                Sequence* sequence = Sequence::create(delay, callback, NULL);
                                Spawn* spawn = Spawn::create(sequence, moveTo, NULL);
                                mainCamera->runAction(spawn);
                                runner->fadeOut();
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
void TerrainPatternLayer::eraseDecorator(Decorator* decorator)
{
    if(!decorator)
        return;
    m_DecoratorList.eraseObject(decorator);
    if(decorator->getReferenceCount() > 0)
        decorator->removeFromParentAndCleanup(true);
    decorator = nullptr;
}
void TerrainPatternLayer::generatePlane()
{
    if(m_patternType == PT_CHECKPOINT || m_patternType == PT_STARTER)
        return;
    if(m_nIndex < 1)
        return;

    float percent1 = 0.1*m_nIndex;
    float percent2 = 1.0 - percent1;
    AlisaMethod* am = AlisaMethod::create(percent1,percent2,-1.0, NULL);
    if(am)
    {
        if(am->getRandomIndex() == 0)
        {
            Decorator* plane = Decorator::create(Decorator::DT_PLANE);
            if(plane)
            {
                float targetX = -100;
                int isLeft = cocos2d::random(0, 1);
                if(isLeft)
                {
                    plane->setRotation3D(Vec3(0, 180, 0));
                    plane->setPositionX(-32.0);
                    targetX = 100;
                }
                else
                {
                    plane->setPositionX(32.0);
                }
                float z = cocos2d::random(-20.0f, -60.0f);
                plane->setPositionZ(z);
                plane->setCameraMask((unsigned short)CameraFlag::USER1);
                addChild(plane);
                m_DecoratorList.pushBack(plane);
                    
                float time = cocos2d::random(1.0f, 2.5f);
                float moveTime = cocos2d::random(1.0f, 1.5f);
                DelayTime* delay = DelayTime::create(time);
                EaseSineOut* fadeIn = EaseSineOut::create(FadeIn::create(0.5f));
                MoveTo* moveTo = MoveTo::create(moveTime, plane->getPosition3D() + Vec3(targetX, 0, 0));
                Spawn* spawn = Spawn::create(fadeIn, moveTo, NULL);
                Sequence* sequence = Sequence::create(delay, spawn, NULL);
                plane->runAction(sequence);
            }
        }
    }
}
void TerrainPatternLayer::generateCheckPointDecorator()
{
    Node* parent = Node::create();
    if(parent)
    {
        Decorator* portal = Decorator::create(Decorator::DT_PORTAL);
        if(portal)
        {
            portal->setScale(0);
            Color3B randomColor = UtilityHelper::randomColor(500,80);
            portal->setColor(randomColor);
            parent->addChild(portal);
            m_DecoratorList.pushBack(portal);
            EffectSprite3D* center = EffectSprite3D::create("3x3x3.c3b");
            if(center)
            {
                center->setColor(UtilityHelper::randomColor(400,80));
                OutlineEffect3D* outline = OutlineEffect3D::create();
                outline->setOutlineColor(Vec3(0.3f, 0.3f, 0.3f));
                outline->setOutlineWidth(0.03f);
                center->addEffect(outline, 1);
                RepeatForever* repeat = RepeatForever::create(RotateBy::create(1.0f, Vec3(270, -270, 0)));
                center->runAction(repeat);
                    
                portal->addChild(center);
            }
            EaseSineOut* scaleTo = EaseSineOut::create(ScaleTo::create(1.0f, 0.8));
            portal->runAction(scaleTo);
        }
        addChild(parent);
        RepeatForever* repeat = RepeatForever::create(RotateBy::create(1.0f, Vec3(0, 90, 0)));
        parent->runAction(repeat);
    }
}
void TerrainPatternLayer::generateDecorator(TerrainCell* cell, int patternIndex)
{
    CCASSERT(patternIndex!=0, "patternIndex not equal to zero");
    if(m_patternType != PT_STARTER && m_patternType != PT_CHECKPOINT)
    {
        if(patternIndex <= 11)
        {
            float percent1 = 0.005*patternIndex;
            float percent2 = 0.0001*patternIndex;
            float percent3 = 0.001*patternIndex;
            float percent4 = 1.0 - percent1 - percent2 - percent3;
            AlisaMethod* am = AlisaMethod::create(percent1,percent2,percent3,percent4,-1.0, NULL);
            if(am)
            {
                if(am->getRandomIndex() == 0)
                {
                    Decorator* gold = Decorator::create(Decorator::DT_GOLD);
                    if(gold)
                    {
                        cell->addChild(gold);
                        m_DecoratorList.pushBack(gold);
                        RepeatForever* repeat = RepeatForever::create(RotateBy::create(1.0f, Vec3(0, 180, 0)));
                        gold->runAction(repeat);
                    }
                }
                else if(am->getRandomIndex() == 1)
                {
                    Decorator* heart = Decorator::create(Decorator::DT_HEART);
                    if(heart)
                    {
                        cell->addChild(heart);
                        m_DecoratorList.pushBack(heart);
                        RepeatForever* repeat = RepeatForever::create(RotateBy::create(1.0f, Vec3(0, 180, 0)));
                        heart->runAction(repeat);
                    }
                }
                else if(am->getRandomIndex() == 2)
                {
                    Decorator* bird = Decorator::create(Decorator::DT_BIRD);
                    if(bird)
                    {
                        cell->addChild(bird);
                        m_DecoratorList.pushBack(bird);
                        
                        float time = cocos2d::random(1.0f, 3.0f);
                        DelayTime* delay = DelayTime::create(time);
                        EaseSineOut* fadeIn = EaseSineOut::create(FadeIn::create(0.5f));
                        CallFunc* callfunc = CallFunc::create(CC_CALLBACK_0(Decorator::setNeedToUpdate, bird, true));
                        Sequence* sequence = Sequence::create(delay, fadeIn, callfunc, NULL);
                        bird->runAction(sequence);
                    }
                }
            }
        }
        else
        {
            float percent1 = 0.005*patternIndex;
            float percent2 = 0.0001*patternIndex;
            float percent3 = 0.0005*patternIndex;
            float percent4 = 0.001*patternIndex;
            float percent5 = 1.0 - percent1 - percent2 - percent3 - percent4;
            AlisaMethod* am = AlisaMethod::create(percent1,percent2,percent3,percent4,percent5,-1.0, NULL);
            if(am)
            {
                if(am->getRandomIndex() == 0)
                {
                    Decorator* gold = Decorator::create(Decorator::DT_GOLD);
                    if(gold)
                    {
                        cell->addChild(gold);
                        m_DecoratorList.pushBack(gold);
                        RepeatForever* repeat = RepeatForever::create(RotateBy::create(1.0f, Vec3(0, 180, 0)));
                        gold->runAction(repeat);
                    }
                }
                else if(am->getRandomIndex() == 1)
                {
                    Decorator* heart = Decorator::create(Decorator::DT_HEART);
                    if(heart)
                    {
                        cell->addChild(heart);
                        m_DecoratorList.pushBack(heart);
                        RepeatForever* repeat = RepeatForever::create(RotateBy::create(1.0f, Vec3(0, 180, 0)));
                        heart->runAction(repeat);
                    }
                }
                else if(am->getRandomIndex() == 2)
                {
                    Decorator* gold = Decorator::create(Decorator::DT_GOLD_BIG);
                    if(gold)
                    {
                        cell->addChild(gold);
                        m_DecoratorList.pushBack(gold);
                        RepeatForever* repeat = RepeatForever::create(RotateBy::create(1.0f, Vec3(0, 180, 0)));
                        gold->runAction(repeat);
                    }
                }
                else if(am->getRandomIndex() == 3)
                {
                    Decorator* bird = Decorator::create(Decorator::DT_BIRD);
                    if(bird)
                    {
                        Runner* runner = RunController::getInstance()->getMainPlayer();
                        if(runner)
                        {
                            cell->addChild(bird);
                            m_DecoratorList.pushBack(bird);
                            
                            float time = cocos2d::random(1.0f, 2.0f);
                            DelayTime* delay = DelayTime::create(time);
                            EaseSineOut* fadeIn = EaseSineOut::create(FadeIn::create(0.5f));
                            CallFunc* callfunc = CallFunc::create(CC_CALLBACK_0(Decorator::setNeedToUpdate, bird, true));
                            Sequence* sequence = Sequence::create(delay, fadeIn, callfunc, NULL);
                            bird->runAction(sequence);
                        }
                    }
                }
            }
                
        }
    }
}