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
USING_NS_CC;
TerrainPatternLayer* TerrainPatternLayer::create(int index)
{
    TerrainPatternLayer *pRet = new(std::nothrow) TerrainPatternLayer();
    if (pRet && pRet->init(index))
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

bool TerrainPatternLayer::init(int index)
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
                }
                break;
                
            default:
                break;
        }
    }
    
    return true;
}
void TerrainPatternLayer::update(float delta)
{
    for (int i = 0; i<m_TerrainCellList.size(); ++i) {
        TerrainCell* cell = m_TerrainCellList.at(i);
        if(cell)
        {
            bool isVisible = RunController::getInstance()->getMainCamera()->isVisibleInFrustum(&cell->getAABB());
            if(!isVisible)
            {
                m_TerrainCellList.eraseObject(cell);
                cell->removeFromParentAndCleanup(true);
                cell = nullptr;
            }
        }
    }
//    Runner* runner = RunController::getInstance()->getMainPlayer();
//    if(!runner || runner->getState() == Runner::RS_IDLE)
//        return;
//    for (TerrainCell* cell : m_TerrainCellList) {
//        if(cell)
//        {
//            bool collision = runner->getModifyAABB().intersects(cell->getAABB());
//            if(collision)
//            {
//                runner->onCollision(cell);
//                return;
//            }
//        }
//    }
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
                onLand(cell);
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
void TerrainPatternLayer::onLand(TerrainCell* cell)
{
    TerrainCell::CellType type = cell->getType();
//    switch (type) {
//        case <#constant#>:
//            <#statements#>
//            break;
//            
//        default:
//            break;
//    }
}
