//
//  GroundLayer.cpp
//  MazeJump
//
//  Created by wang haibo on 15/6/24.
//
//

#include "GroundLayer.h"
#include "UtilityHelper.h"
#include "GroundLayer.h"
USING_NS_CC;

GroundLayer* GroundLayer::create(const std::string& tmxFile)
{
    GroundLayer *pRet = new(std::nothrow) GroundLayer();
    if (pRet && pRet->init(tmxFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}
GroundLayer::GroundLayer()
{
    m_fCellRadius = 5.0f;
    m_Offset = Vec3::ZERO;
    m_pArrowUp = nullptr;
    m_pArrowDown = nullptr;
    m_pArrowLeft = nullptr;
    m_pArrowRight = nullptr;
    m_pCurrentCell = nullptr;
    m_pPlayer = nullptr;
    m_pCamera = nullptr;
}

bool GroundLayer::init(const std::string& tmxFile)
{
    if ( !Layer::init() )
        return false;
    
    TMXMapInfo *mapInfo = TMXMapInfo::create(tmxFile);
    if (!mapInfo || mapInfo->getObjectGroups().size() < 1)
        return false;
    
    m_MapSize = mapInfo->getMapSize();
    
    cocos2d::TMXObjectGroup* objectGroup = mapInfo->getObjectGroups().at(0);
    if(objectGroup->getObjects().size() == m_MapSize.width * m_MapSize.height)
    {
        for (int i = 0; i<m_MapSize.height; i++) {
            for (int j = 0; j<m_MapSize.width; j++) {
                GroundCell* cell = GroundCell::create();
                if(cell)
                {
                    int index = i*m_MapSize.width + j;
                    Value value = objectGroup->getObjects().at(index);
                    int type = value.asValueMap()["type"].asInt();
                    cell->setType(GroundCell::CellType(type));
                    m_fCellRadius = cell->getRadius();
                    cell->setPosition3D(Vec3(i*(cell->getRadius())*2, -40, j*(cell->getRadius())*2));
                    cell->setScale(0.9f);
                    cell->setOpacity(0);
                    cell->setIndexX(j);
                    cell->setIndexY(i);
                    addChild( cell );
                    m_GroundCellList.pushBack(cell);
                    
                    switch (type) {
                        case GroundCell::CT_HIDE:
                            cell->setVisible(false);
                            break;
                        default:
                            break;
                    }

                    float time = cocos2d::random(0.8f, 1.6f);
                    EaseBackInOut* moveTo = EaseBackInOut::create(MoveTo::create(time, Vec3(i*(cell->getRadius())*2, 0, j*(cell->getRadius())*2)));
                    EaseExponentialIn* fadeIn = EaseExponentialIn::create(FadeIn::create(time*0.5f));
                    Spawn* spawn = Spawn::createWithTwoActions(moveTo, fadeIn);
                    float delayTime = cocos2d::random(0.0f, 0.2f);
                    DelayTime* delay = DelayTime::create(delayTime);
                    Sequence* sequence = Sequence::createWithTwoActions(delay, spawn);
                    cell->runAction(sequence);
                }
            }
        }
        m_Offset = Vec3((m_MapSize.width-1)*m_fCellRadius , 0, (m_MapSize.height-1)*m_fCellRadius);
    }
    
    m_pArrowUp = Arrow::create(Arrow::AT_UP);
    if(!m_pArrowUp)
        return false;
    m_pArrowUp->setVisible(false);
    m_pArrowUp->setScale(0.9f);
    addChild(m_pArrowUp);
    
    m_pArrowDown = Arrow::create(Arrow::AT_DOWN);
    if(!m_pArrowDown)
        return false;
    m_pArrowDown->setVisible(false);
    m_pArrowDown->setScale(0.9f);
    m_pArrowDown->setRotation3D(Vec3(0,180,0));
    addChild(m_pArrowDown);
    
    m_pArrowLeft = Arrow::create(Arrow::AT_LEFT);
    if(!m_pArrowLeft)
        return false;
    m_pArrowLeft->setVisible(false);
    m_pArrowLeft->setScale(0.9f);
    m_pArrowLeft->setRotation3D(Vec3(0,90,0));
    addChild(m_pArrowLeft);
    
    m_pArrowRight = Arrow::create(Arrow::AT_RIGHT);
    if(!m_pArrowRight)
        return false;
    m_pArrowRight->setVisible(false);
    m_pArrowRight->setScale(0.9f);
    m_pArrowRight->setRotation3D(Vec3(0,-90,0));
    addChild(m_pArrowRight);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchAllAtOnce::create();
    if(touchListener == nullptr)
        return false;
    touchListener->onTouchesBegan = CC_CALLBACK_2(GroundLayer::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(GroundLayer::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(GroundLayer::onTouchesEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}
Vector<GroundCell*> GroundLayer::getNeighborCells(GroundCell* currentCell)
{
    Vector<GroundCell*> cells;
    if(currentCell != nullptr)
    {
        ///down
        int indexX = currentCell->getIndexX();
        int indexY = currentCell->getIndexY()-1;
        if(indexY >= 0 && indexY < m_MapSize.height)
        {
            int index = indexY*m_MapSize.height + indexX;
            GroundCell* neighborCell = m_GroundCellList.at(index);
            if(neighborCell && m_pPlayer)
            {
                switch (m_pPlayer->getType()) {
                    case Player::PT_STRENGTH:
                    {
                        if (neighborCell->getType() == GroundCell::CT_NOT || neighborCell->getType() == GroundCell::CT_BOMB) {
                            cells.pushBack(neighborCell);
                        }
                    }
                    break;
                        
                    default:
                        break;
                }
            }
        }
        ////up
        indexX = currentCell->getIndexX();
        indexY = currentCell->getIndexY()+1;
        if(indexY >= 0 && indexY < m_MapSize.height)
        {
            int index = indexY*m_MapSize.height + indexX;
            GroundCell* neighborCell = m_GroundCellList.at(index);
            if(neighborCell && m_pPlayer)
            {
                switch (m_pPlayer->getType()) {
                    case Player::PT_STRENGTH:
                    {
                        if (neighborCell->getType() == GroundCell::CT_NOT || neighborCell->getType() == GroundCell::CT_BOMB) {
                            cells.pushBack(neighborCell);
                        }
                    }
                        break;
                        
                    default:
                        break;
                }
            }
        }
        ///left
        indexX = currentCell->getIndexX() - 1;
        indexY = currentCell->getIndexY();
        if(indexX >= 0 && indexX < m_MapSize.width)
        {
            int index = indexY*m_MapSize.height + indexX;
            GroundCell* neighborCell = m_GroundCellList.at(index);
            if(neighborCell && m_pPlayer)
            {
                switch (m_pPlayer->getType()) {
                    case Player::PT_STRENGTH:
                    {
                        if (neighborCell->getType() == GroundCell::CT_NOT || neighborCell->getType() == GroundCell::CT_BOMB) {
                            cells.pushBack(neighborCell);
                        }
                    }
                        break;
                        
                    default:
                        break;
                }
            }
        }
        ////right
        indexX = currentCell->getIndexX() + 1;
        indexY = currentCell->getIndexY();
        if(indexX >= 0 && indexX < m_MapSize.width)
        {
            int index = indexY*m_MapSize.height + indexX;
            GroundCell* neighborCell = m_GroundCellList.at(index);
            if(neighborCell && m_pPlayer)
            {
                switch (m_pPlayer->getType()) {
                    case Player::PT_STRENGTH:
                    {
                        if (neighborCell->getType() == GroundCell::CT_NOT || neighborCell->getType() == GroundCell::CT_BOMB) {
                            cells.pushBack(neighborCell);
                        }
                    }
                        break;
                        
                    default:
                        break;
                }
            }
        }

    }
    return cells;
}
GroundCell* GroundLayer::getNextCell(int nextIndexX, int nextIndexY)
{
    int nextIndex = nextIndexY*m_MapSize.height + nextIndexX;
    return m_GroundCellList.at(nextIndex);
}

void GroundLayer::flipIndexCell(int indexX, int indexY)
{
    if(indexX < 0 || indexX >= m_MapSize.width)
        return;
    if(indexY < 0 || indexY >= m_MapSize.height)
        return;
    
    int index = indexY*m_MapSize.width + indexX;
    m_pCurrentCell = m_GroundCellList.at(index);
    if(m_pCurrentCell && m_pPlayer)
    {
        RotateTo* ratateTo = nullptr;
        switch (m_pPlayer->getPlayerState()) {
            case Player::PS_MOVE_LEFT:
                ratateTo = RotateTo::create(0.3f, Vec3(-180,0,0));
                break;
            case Player::PS_MOVE_RIGHT:
                ratateTo = RotateTo::create(0.3f, Vec3(180,0,0));
                break;
            case Player::PS_MOVE_UP:
                ratateTo = RotateTo::create(0.3f, Vec3(0,0,180));
                break;
            case Player::PS_MOVE_DOWN:
                ratateTo = RotateTo::create(0.3f, Vec3(0,0,-180));
                break;
            default:
                break;
        }
        
        MoveTo* moveTo = MoveTo::create(0.3f, Vec3(m_pCurrentCell->getPositionX(), 2, m_pCurrentCell->getPositionZ()));
        Spawn* spawn = Spawn::createWithTwoActions(ratateTo, moveTo);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(GroundLayer::setCurrentCellTypeOK,this));
        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
        m_pCurrentCell->runAction(sequence);
    }
}

void GroundLayer::setCurrentCellTypeOK()
{
    if(m_pCurrentCell)
    {
        m_pCurrentCell->setType(GroundCell::CT_OK);
        if(m_pPlayer == nullptr)
        {
            m_pPlayer = Player::create(Player::PT_STRENGTH, this);
            if(m_pPlayer)
            {
                m_pPlayer->setIndexX(m_pCurrentCell->getIndexX());
                m_pPlayer->setIndexY(m_pCurrentCell->getIndexY());
                m_pPlayer->setCameraMask((unsigned short)CameraFlag::USER1);
                m_pPlayer->setPosition3D(m_pCurrentCell->getPosition3D());
                m_pPlayer->setScale(0.9f);
                m_pPlayer->setPlayerState(Player::PS_IDLE);
                addChild(m_pPlayer);
            }
        }
    }
}
void GroundLayer::showArrow()
{
    Vector<GroundCell*> neighborCells = getNeighborCells(m_pCurrentCell);
    for (int i = 0; i < neighborCells.size(); ++i) {
        GroundCell* cell = neighborCells.at(i);
        if(cell)
        {
            if(cell->getIndexY() == m_pCurrentCell->getIndexY())
            {
                if (cell->getIndexX() > m_pCurrentCell->getIndexX()) {
                    m_pArrowRight->setVisible(true);
                    m_pArrowRight->setIndexX(cell->getIndexX());
                    m_pArrowRight->setIndexY(cell->getIndexY());
                    m_pArrowRight->setPosition3D(cell->getPosition3D() + Vec3(0,2,0));
                }
                else if(cell->getIndexX() < m_pCurrentCell->getIndexX()) {
                    m_pArrowLeft->setVisible(true);
                    m_pArrowLeft->setIndexX(cell->getIndexX());
                    m_pArrowLeft->setIndexY(cell->getIndexY());
                    m_pArrowLeft->setPosition3D(cell->getPosition3D() + Vec3(0,2,0));
                }
            }
            if(cell->getIndexX() == m_pCurrentCell->getIndexX())
            {
                if (cell->getIndexY() > m_pCurrentCell->getIndexY()) {
                    m_pArrowUp->setVisible(true);
                    m_pArrowUp->setIndexX(cell->getIndexX());
                    m_pArrowUp->setIndexY(cell->getIndexY());
                    m_pArrowUp->setPosition3D(cell->getPosition3D() + Vec3(0,2,0));
                }
                else if(cell->getIndexY() < m_pCurrentCell->getIndexY()) {
                    m_pArrowDown->setVisible(true);
                    m_pArrowDown->setIndexX(cell->getIndexX());
                    m_pArrowDown->setIndexY(cell->getIndexY());
                    m_pArrowDown->setPosition3D(cell->getPosition3D() + Vec3(0,2,0));
                }
            }
        }
    }
}
void GroundLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
    if(touches.size() > 0)
    {
        Vec2 locationInNode = convertToNodeSpace(touches[0]->getLocation());
        Ray ray;
        UtilityHelper::getCameraToViewportRay(m_pCamera, locationInNode, &ray);
        if(m_pCurrentCell == nullptr)
        {
            for (int i = 0; i< m_GroundCellList.size(); i++) {
                GroundCell* cell = m_GroundCellList.at(i);
                if(cell)
                {
                    if(ray.intersects(cell->getAABB()) && cell->getType() == GroundCell::CT_NOT)
                    {
                        m_pCurrentCell = cell;
                        RotateTo* ratateTo = RotateTo::create(0.5f, Vec3(180,0,0));
                        MoveTo* moveTo = MoveTo::create(0.5f, Vec3(cell->getPositionX(), 2, cell->getPositionZ()));
                        Spawn* spawn = Spawn::createWithTwoActions(ratateTo, moveTo);
                        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(GroundLayer::setCurrentCellTypeOK,this));
                        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
                        cell->runAction(sequence);
                        break;
                    }
                }
            }
        }
        else
        {
            if(m_pArrowDown && m_pArrowDown->isVisible())
            {
                if(ray.intersects(m_pArrowDown->getAABB()) && m_pArrowDown->getType() == Arrow::AT_DOWN)
                {
                    m_pArrowDown->setVisible(false);
                    m_pArrowLeft->setVisible(false);
                    m_pArrowRight->setVisible(false);
                    m_pArrowUp->setVisible(false);
                    if (m_pPlayer)
                        m_pPlayer->setPlayerState(Player::PS_MOVE_DOWN);
                }
            }
            if(m_pArrowLeft && m_pArrowLeft->isVisible())
            {
                if(ray.intersects(m_pArrowLeft->getAABB()) && m_pArrowLeft->getType() == Arrow::AT_LEFT)
                {
                    m_pArrowDown->setVisible(false);
                    m_pArrowLeft->setVisible(false);
                    m_pArrowRight->setVisible(false);
                    m_pArrowUp->setVisible(false);
                    if (m_pPlayer)
                        m_pPlayer->setPlayerState(Player::PS_MOVE_LEFT);
                }
            }
            if(m_pArrowRight && m_pArrowRight->isVisible())
            {
                if(ray.intersects(m_pArrowRight->getAABB()) && m_pArrowRight->getType() == Arrow::AT_RIGHT)
                {
                    m_pArrowDown->setVisible(false);
                    m_pArrowLeft->setVisible(false);
                    m_pArrowRight->setVisible(false);
                    m_pArrowUp->setVisible(false);
                    if (m_pPlayer)
                        m_pPlayer->setPlayerState(Player::PS_MOVE_RIGHT);
                }
            }
            if(m_pArrowUp && m_pArrowUp->isVisible())
            {
                if(ray.intersects(m_pArrowUp->getAABB()) && m_pArrowUp->getType() == Arrow::AT_UP)
                {
                    m_pArrowDown->setVisible(false);
                    m_pArrowLeft->setVisible(false);
                    m_pArrowRight->setVisible(false);
                    m_pArrowUp->setVisible(false);
                    if (m_pPlayer)
                        m_pPlayer->setPlayerState(Player::PS_MOVE_UP);
                }
            }
        }
    }
}
void GroundLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
{
}
void GroundLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
}