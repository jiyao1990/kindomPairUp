//
//  GameScene.cpp
//  kindomPairUp
//
//  Created by Jiyao on 14/11/3.
//
//

#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TopSprite.h"
#include "CardFactory.h"

//using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

GameScene::GameScene()
{
    chooseCoord.hor = 0;
    chooseCoord.row = 0;
    endCoord.hor = 0;
    endCoord.row = 0;
    startPoint.set(0, 0);
    endPoint.set(0, 0);
    box = NULL;
    field = NULL;
    isMoving = false;
}
GameScene::~GameScene()
{
    chooseCoord.hor = 0;
    chooseCoord.row = 0;
    endCoord.hor = 0;
    endCoord.row = 0;
    startPoint.set(0, 0);
    endPoint.set(0, 0);
    box = NULL;
    field = NULL;
    isMoving = false;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    this->initWithColor(Color4B(184, 244, 255, 255));
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
    listener->setSwallowTouches(true);//不向下传递触摸
    dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    auto rootNode = CSLoader::createNode("GameScene.csb");
    
    addChild(rootNode);
    
    auto bgLayer = rootNode->getChildByName("bgLayer");
    auto pauseBg = rootNode->getChildByName("pauseBg");
    
    auto boxBg = bgLayer->getChildByName("boxBg");
    box = (Sprite*)boxBg->getChildByName("box");
    field = (Sprite*)boxBg->getChildByName("grass")->getChildByName("field");
    //    auto startItem = static_cast<ui::Button*>(bgLayer->getChildByName("btn_start"));
    //    startItem->addTouchEventListener(CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
    
    gGlobal->fullScreen(rootNode);
    gGlobal->scaleFitInScreen_Child(bgLayer);
    gGlobal->scaleFitInScreen_Child(pauseBg);
    
    initGame();
    
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::handlerMsg));

    return true;
}

void GameScene::initGame()
{
    for (int i = GameType_house;  i < GameType_len; i++) {
        
        topSp[i] = TopSprite::create((GameType)i, TypeLevel_1);
        
        field->addChild(topSp[i]);
        
        topSp[i]->setAnchorPoint(Vec2(0.5, 0));
        
        topSp[i]->setPosition(Vec2((field->getContentSize().width / TypeNum) * (i + 0.5) , field->getContentSize().height / 2 - 10));
    }
    
    for (int i = 0 ; i < TileHor; i ++) {
        
        for (int j= 0 ; j < TileRow; j++) {
            
            GameType n = (GameType)createRandomValue((int)GameType_house, (int)GameType_traffic);
            
            gameTile[i][j] = CardFactory::getCard(n, TypeLevel_1);
            
            box->addChild(gameTile[i][j]);
//            log("%f,%f",(box->getContentSize().width / TileRow) * (j + 0.5),(box->getContentSize().height / TileHor) * (i + 0.5));
            Coord _coord;
            _coord.hor = i;
            _coord.row = j;
            setPositionByCoor(_coord);
            
        }
        
    }
    
    //更换可以消除的card
    
    for (int i = 0 ; i < TileHor; i ++) {
        
        for (int j= 0 ; j < TileRow; j++) {
            Coord _coord;
            _coord.hor = i;
            _coord.row = j;
            while (checkIsCanPairUp(_coord)) {
                GameType n = (GameType)createRandomValue((int)GameType_house, (int)GameType_traffic);
                
                gameTile[i][j]->changeCard(n, TypeLevel_1);
            }
        }
    }
    
}

bool GameScene::checkIsCanPairUp(Coord coord)
{
    if (pairUpVec.size() > 0) {
        pairUpVec.clear();
    }
    Coord _coord = coord;
    GameType type = gameTile[_coord.hor][_coord.row]->getType();
    TypeLevel _level = gameTile[_coord.hor][_coord.row]->getLevel();
    int count = 1;
    bool flag = false;
//    CCLOG("%d,%d,%d",coord.hor,coord.row,type);
    //上边
    for (int i = _coord.hor + 1 ; i < TileHor; i ++) {
        if (type == gameTile[i][_coord.row]->getType() && _level == gameTile[i][_coord.row]->getLevel()) {
            count ++;
            Coord tempCoord;
            tempCoord.hor = i;
            tempCoord.row = _coord.row;
            pairUpVec.push_back(tempCoord);
        }else{
            break;
        }
    }
    //下边
    for (int i = _coord.hor - 1; i >= 0; i --) {
        if (type == gameTile[i][_coord.row]->getType() && _level == gameTile[i][_coord.row]->getLevel()) {
            count ++;
            Coord tempCoord;
            tempCoord.hor = i;
            tempCoord.row = _coord.row;
            pairUpVec.push_back(tempCoord);
        }else{
            break;
        }
    }
    
    if (count >= 3) {
        flag = true;
    }else{
        count = 1;
        pairUpVec.clear();
    }
    
    //右边
    for (int i = _coord.row + 1; i < TileRow; i ++) {
        if (type == gameTile[_coord.hor][i]->getType() && _level == gameTile[_coord.hor][i]->getLevel()) {
            count ++;
            Coord tempCoord;
            tempCoord.hor = _coord.hor;
            tempCoord.row = i;
            pairUpVec.push_back(tempCoord);
        }else{
            break;
        }
    }
    //左边
    for (int i = _coord.row - 1; i >= 0; i --) {
        if (type == gameTile[_coord.hor][i]->getType() && _level == gameTile[_coord.hor][i]->getLevel()) {
            count ++;
            Coord tempCoord;
            tempCoord.hor = _coord.hor;
            tempCoord.row = i;
            pairUpVec.push_back(tempCoord);
        }else{
            break;
        }
    }
    
    
    if (count >= 3) {
        flag = true;
    }else{
        count = 1;
        pairUpVec.clear();
    }
    
    
    return flag;
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
    Vec2 point = touch->getLocation();
    startPoint = point;
    for (int i = 0 ; i < TileHor; i ++) {
        
        for (int j= 0 ; j < TileRow; j++) {
            
            if(gameTile[i][j]->getBoundingBox().containsPoint(point))
            {
                GameType type = gameTile[i][j]->getType();
                chooseCoord.hor = i;
                chooseCoord.row = j;
                gameTile[i][j]->setScale(1.2f);
                highlightWithType(type);
            }
            
        }
    }
    
    return true;
}
void GameScene::onTouchMoved(Touch *touch, Event *unused_event)
{
    Vec2 prePoint = touch->getPreviousLocation();
    Vec2 point = touch->getLocation();
    
    
    
}
void GameScene::onTouchEnded(Touch *touch, Event *unused_event)
{
    if (chooseCoord.row == -1 || chooseCoord.hor == -1) {
        return;
    }

    Vec2 point = touch->getLocation();
    endPoint = point;
    float slideX = endPoint.x - startPoint.x;
    float slideY = endPoint.y - startPoint.y;
    gameTile[chooseCoord.hor][chooseCoord.row]->setScale(1.f);

    if (fabs(slideX) > fabs(slideY)) {
        
        if (slideX > 50) {
            
            if (chooseCoord.row < TileRow - 1) {
                
                Coord tempCoord;
                tempCoord.hor = chooseCoord.hor;
                tempCoord.row = chooseCoord.row + 1;
                
                exchangeCard(chooseCoord, tempCoord);
            }
            
        }else if (slideX < -50){
            
            if (chooseCoord.row > 0) {
                
                Coord tempCoord;
                tempCoord.hor = chooseCoord.hor;
                tempCoord.row = chooseCoord.row - 1;
                
                exchangeCard(chooseCoord, tempCoord);
            }
            
            
        }
        
        
    }else{
        
        if (slideY > 50) {
            
            if (chooseCoord.hor < TileHor - 1) {
                
                Coord tempCoord;
                tempCoord.hor = chooseCoord.hor + 1;
                tempCoord.row = chooseCoord.row;
                
                exchangeCard(chooseCoord, tempCoord);

            }
            
        }else if (slideY < -50){
            
            if (chooseCoord.hor > 0) {
                Coord tempCoord;
                tempCoord.hor = chooseCoord.hor - 1;
                tempCoord.row = chooseCoord.row;
                
                exchangeCard(chooseCoord, tempCoord);
            
            }
            
            
        }
        
    }
    
    
    
    if (box->getChildByName("mask")) {
        box->getChildByName("mask")->removeFromParent();
    }
    
    chooseCoord.hor = -1;
    chooseCoord.row = -1;
    
}

void GameScene::highlightWithType(GameType type)
{
    if (!box->getChildByName("mask")) {
        LayerColor* mask = LayerColor::create(Color4B(0, 0, 0, 100), box->getContentSize().width, box->getContentSize().height);
        box->addChild(mask);
        mask->setLocalZOrder(Zorder_Mask);
        mask->setName("mask");
    }
    for (int i = 0 ; i < TileHor; i ++) {
        
        for (int j= 0 ; j < TileRow; j++) {
            
            if(gameTile[i][j]->getType() == type)
            {
//                gameTile[i][j]->setOpacity(150);
                gameTile[i][j]->setLocalZOrder(Zorder_Chose);
            }else{
                gameTile[i][j]->setLocalZOrder(Zorder_Min);
            }
            
        }
    }
}

//计时器
void GameScene::handlerMsg(float dt)
{
//    if (isMoving) {
//        moveTimer += dt;
//        log("%f",moveTimer);
//        if (moveTimer >= moveTime) {
//            moveTimer = 0;
//            isMoving = false;
//        }
//    }
    
    
}

void GameScene::exchangeCard(Coord coord1, Coord coord2)
{
    bool isPairUp = false;
    if (!isMoving) {
        log("moving");
        isMoving = true;
        ActionInterval* move1To2 = MoveTo::create(moveTime, gameTile[coord2.hor][coord2.row]->getPosition());
        ActionInterval* move2To1 = MoveTo::create(moveTime, gameTile[coord1.hor][coord1.row]->getPosition());
        gameTile[coord1.hor][coord1.row]->runAction(move1To2);
        gameTile[coord2.hor][coord2.row]->runAction(move2To1);
        
        CardSprite* temp = gameTile[coord1.hor][coord1.row];
        gameTile[coord1.hor][coord1.row] = gameTile[coord2.hor][coord2.row];
        gameTile[coord2.hor][coord2.row] = temp;
        
        
        if (checkIsCanPairUp(coord1)) {
            for (int i = 0; i < pairUpVec.size() ; i ++) {
                Coord _coord = pairUpVec.at(i);
                gameTile[_coord.hor][_coord.row]->runAction(Sequence::create(MoveTo::create(moveTime, gameTile[coord2.hor][coord2.row]->getPosition()), CallFunc::create(CC_CALLBACK_0(GameScene::pairUpAndLevelUp, this, coord1)), CallFunc::create(CC_CALLBACK_0(GameScene::endMoving, this)), NULL) );
            }
            isPairUp = true;
        }else{
            isPairUp = false;
        }
        
        if (checkIsCanPairUp(coord2)) {
            for (int i = 0; i < pairUpVec.size() ; i ++) {
                Coord _coord = pairUpVec.at(i);
                gameTile[_coord.hor][_coord.row]->runAction(Sequence::create(MoveTo::create(moveTime, gameTile[coord1.hor][coord1.row]->getPosition()), CallFunc::create(CC_CALLBACK_0(GameScene::pairUpAndLevelUp, this,coord2)), CallFunc::create(CC_CALLBACK_0(GameScene::endMoving, this)), NULL) );
            }
            isPairUp = true;
        }
        
        if (!isPairUp) {
            gameTile[coord1.hor][coord1.row]->runAction(Sequence::create(DelayTime::create(moveTime), move1To2, CallFunc::create(CC_CALLBACK_0(GameScene::endMoving, this)), NULL) );
            gameTile[coord2.hor][coord2.row]->runAction(Sequence::create(DelayTime::create(moveTime), move2To1, CallFunc::create(CC_CALLBACK_0(GameScene::endMoving, this)), NULL) );
            
            CardSprite* temp = gameTile[coord1.hor][coord1.row];
            gameTile[coord1.hor][coord1.row] = gameTile[coord2.hor][coord2.row];
            gameTile[coord2.hor][coord2.row] = temp;
            
        }
        
        
    }
}

void GameScene::endMoving()
{
    isMoving = false;
}

void GameScene::pairUpAndLevelUp(Coord coord)
{
    GameType _type = gameTile[coord.hor][coord.row]->getType();
    TypeLevel _level = gameTile[coord.hor][coord.row]->getLevel();
    if (_level < TypeLevel_5) {
        _level = (TypeLevel)((int)_level + 1);
    }
    gameTile[coord.hor][coord.row]->changeCard(_type, _level);
    
    for (int i = 0; i < pairUpVec.size() ; i ++) {
        Coord _coord = pairUpVec.at(i);
        gameTile[_coord.hor][_coord.row]->removeFromParent();
        gameTile[_coord.hor][_coord.row]->isPairUp = true;
    }
    
    setPositionByCoor(coord);
    
    cardDrop();

}

void GameScene::cardDrop()
{

    for (int i = 0; i < pairUpVec.size() ; i ++) {
        Coord _coord = pairUpVec.at(i);
        for (int m = _coord.hor + 1 ; m < TileHor ; m ++) {
            if (!gameTile[m][_coord.row]->isPairUp) {
                Coord tempCoord;
                tempCoord.hor = m - 1;
                tempCoord.row = _coord.row;
                gameTile[m - 1][_coord.row] = gameTile[m][_coord.row];
                gameTile[m - 1][_coord.row]->isPairUp = false;
                gameTile[m][_coord.row]->isPairUp = true;
                setPositionByCoor(tempCoord, true);
            }
        }
    }
    
}

//根据坐标设置位置
void GameScene::setPositionByCoor(Coord coord, bool isAction)
{
    int i = coord.hor;
    int j = coord.row;
    
    if (isAction) {
        gameTile[i][j]->runAction(MoveTo::create(moveTime, Vec2((box->getContentSize().width / TileRow) * (j + 0.5) ,((box->getContentSize().height - 60) / TileHor) * (i + 0.5) + 5)));
//        gameTile[i][j]->setMyPosition(Vec2((box->getContentSize().width / TileRow) * (j + 0.5) ,((box->getContentSize().height - 60) / TileHor) * (i + 0.5) + 5));
    }else{
        gameTile[i][j]->setPosition(Vec2((box->getContentSize().width / TileRow) * (j + 0.5) ,((box->getContentSize().height - 60) / TileHor) * (i + 0.5) + 5));
//        gameTile[i][j]->setMyPosition(Vec2((box->getContentSize().width / TileRow) * (j + 0.5) ,((box->getContentSize().height - 60) / TileHor) * (i + 0.5) + 5));
    }
    
}
