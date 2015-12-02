//
//  NursePopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/1.
//
//

#include "NursePopupUI.hpp"

NursePopupUI::NursePopupUI()
{
    
}
NursePopupUI::~NursePopupUI()
{
    
}

bool NursePopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
    return load("",false);
}

bool NursePopupUI::addEvents()
{
    if (!PopupUILayer::addEvents())
        return false;
    return true;
}
void NursePopupUI::refreshUIView()
{
    PopupUILayer::refreshUIView();
        
}