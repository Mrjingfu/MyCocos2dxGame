//
//  OldLadyPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/1.
//
//

#include "AlchemyPopupUI.hpp"
AlchemyPopupUI::AlchemyPopupUI()
{
    
}
AlchemyPopupUI::~AlchemyPopupUI()
{
    
}

bool AlchemyPopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
    return load("",false);
}

bool AlchemyPopupUI::addEvents()
{
    if (!PopupUILayer::addEvents())
        return false;
    return true;
}
void AlchemyPopupUI::refreshUIView()
{
    PopupUILayer::refreshUIView();
    
}