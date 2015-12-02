//
//  LittleWitchPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/1.
//
//

#include "LittleWitchPopupUI.hpp"
LittleWitchPopupUI::LittleWitchPopupUI()
{
    
}
LittleWitchPopupUI::~LittleWitchPopupUI()
{
    
}

bool LittleWitchPopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
    return load("",false);
}

bool LittleWitchPopupUI::addEvents()
{
    if (!PopupUILayer::addEvents())
        return false;
    return true;
}
void LittleWitchPopupUI::refreshUIView()
{
    PopupUILayer::refreshUIView();
    
}