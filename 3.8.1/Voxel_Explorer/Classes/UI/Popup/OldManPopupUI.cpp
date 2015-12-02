//
//  OldManPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/1.
//
//

#include "OldManPopupUI.hpp"
OldManPopupUI::OldManPopupUI()
{
    
}
OldManPopupUI::~OldManPopupUI()
{
    
}

bool OldManPopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
    return load("",false);
}

bool OldManPopupUI::addEvents()
{
    if (!PopupUILayer::addEvents())
        return false;
    return true;
}
void OldManPopupUI::refreshUIView()
{
    PopupUILayer::refreshUIView();
    
}