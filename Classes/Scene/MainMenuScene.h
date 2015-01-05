//
//  MainMenuScene.h
//  kindomPairUp
//
//  Created by Jiyao on 14/11/3.
//
//

#ifndef __kindomPairUp__MainMenuScene__
#define __kindomPairUp__MainMenuScene__

#include "cocos2d.h"
#include "Global.h"

USING_NS_CC;
class MainMenuScene : public LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void btn_startCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
};

#endif /* defined(__kindomPairUp__MainMenuScene__) */
