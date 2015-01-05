//
//  MainMenuScene.cpp
//  kindomPairUp
//
//  Created by Jiyao on 14/11/3.
//
//

#include "MainMenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"

//using namespace cocostudio::timeline;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    this->initWithColor(Color4B(184, 244, 255, 255));
    
    auto rootNode = CSLoader::createNode("MainMenuScene.csb");
    
    addChild(rootNode);
    
    auto bgLayer = rootNode->getChildByName("bgLayer");
    
    auto startItem = static_cast<ui::Button*>(bgLayer->getChildByName("btn_start"));
    startItem->addClickEventListener(CC_CALLBACK_1(MainMenuScene::btn_startCallback, this));
    
    gGlobal->fullScreen(rootNode);
    gGlobal->scaleFitInScreen_Child(bgLayer);
    
    return true;
}

// a selector callback
void MainMenuScene::btn_startCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->replaceScene(GameScene::createScene());
}
