//
//  WeirdoPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/1.
//
//

#include "GamblePopupUI.hpp"
GamblePopupUI::GamblePopupUI()
{
    
}
GamblePopupUI::~GamblePopupUI()
{
    
}

bool GamblePopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
    return load("",false);
}

bool GamblePopupUI::addEvents()
{
    if (!PopupUILayer::addEvents())
        return false;
    return true;
}
void GamblePopupUI::refreshUIView()
{
    PopupUILayer::refreshUIView();
    
}