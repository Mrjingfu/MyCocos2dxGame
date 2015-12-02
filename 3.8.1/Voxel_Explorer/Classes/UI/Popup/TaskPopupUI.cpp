//
//  ChildPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/1.
//
//

#include "TaskPopupUI.hpp"
TaskPopupUI::TaskPopupUI()
{
    
}
TaskPopupUI::~TaskPopupUI()
{
    
}

bool TaskPopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
    return load("",false);
}

bool TaskPopupUI::addEvents()
{
    if (!PopupUILayer::addEvents())
        return false;
    return true;
}
void TaskPopupUI::refreshUIView()
{
    PopupUILayer::refreshUIView();
    
}