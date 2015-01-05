//
//  GameScene.h
//  kindomPairUp
//
//  Created by Jiyao on 14/11/3.
//
//

#ifndef __kindomPairUp__GameScene__
#define __kindomPairUp__GameScene__

#include "cocos2d.h"
#include "Global.h"
#include "CardSprite.h"

#define moveTime 0.2f

USING_NS_CC;

struct Coord {
    
    int hor;
    int row;
    
};

class GameScene : public LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    //检查是否可以消除，如果可以返回坐标，不可以返回NULL
    bool checkIsCanPairUp(Coord coord);
    
private:
    GameScene();
    ~GameScene();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    void initGame();
    //半透明其他类型
    void highlightWithType(GameType type);
    //计时器
    void handlerMsg(float dt);
    //交换卡片
    void exchangeCard(Coord coord1, Coord coord2);
    //控制是否移动结束
    void endMoving();
    //消除并升级
    void pairUpAndLevelUp(Coord coord);
    //card下落
    void cardDrop();
    //根据坐标设置位置
    void setPositionByCoor(Coord coord, bool isAction = false);
    
    Sprite* box;
    Sprite* field;
    Sprite* topSp[TypeNum];
    int level[TypeNum];
    CardSprite* gameTile[TileHor][TileRow];
    Coord chooseCoord;
    Coord endCoord;
    Point startPoint;
    Point endPoint;
    bool isMoving;
    float moveTimer;
    vector<Coord> pairUpVec;
};


#endif /* defined(__kindomPairUp__GameScene__) */
