//
//  Global.cpp
//  kindomPairUp
//
//  Created by Jiyao on 14/11/3.
//
//

#include "Global.h"

Global*  Global::_instance = NULL;

Global*  Global::getInstance()
{
    if (!_instance) {
        _instance = new Global();
        _instance->init();
    }
    return _instance;
}

bool Global::init()
{
    if (!Node::init()) {
        return  false;
    }

    m_defaultWinSize = Size(640, 960);
    m_WinSize = Director::getInstance()->getWinSize();
    
    return true;
}

float Global::getFitX()
{
    return m_WinSize.width / m_defaultWinSize.width;
}

float Global::getFitY()
{
    return m_WinSize.height / m_defaultWinSize.height;
}

void Global::fitInScreen(Node* pNode)
{
    float _fit = getFitX() > getFitY() ? getFitY() : getFitX();
    pNode->setScale(_fit);
}

void Global::fitOutScreen(Node* pNode)
{
    float _fit = getFitX() < getFitY() ? getFitY() : getFitX();
    pNode->setScale(_fit);
}

void Global::fullScreen(Node* pNode)
{
    pNode->setScaleX(getFitX());
    pNode->setScaleY(getFitY());
}

void Global::scaleFitInScreen_Child(cocos2d::Node *_node)
{
    CCAssert(_node != NULL && _node->getParent() != NULL, "scaleFitInScreen_Child : pointer can't be null!");
    
    Node* _parentNode = _node->getParent();
    float totalParentScaleX = 1.0f;
    float totalParentScaleY = 1.0f;
    
    while (_parentNode)
    {
        totalParentScaleX *= _parentNode->getScaleX();
        totalParentScaleY *= _parentNode->getScaleY();
        
        _parentNode = _parentNode->getParent();
    }
    float _scaleFit = getFitX() > getFitY() ? getFitY() : getFitX();
    totalParentScaleX = (_scaleFit / totalParentScaleX) * _node->getScaleX();
    totalParentScaleY = (_scaleFit / totalParentScaleY) * _node->getScaleY();
    
    _node->setScaleX(totalParentScaleX);
    _node->setScaleY(totalParentScaleY);
}


