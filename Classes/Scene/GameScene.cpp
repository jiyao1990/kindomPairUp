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
    chooseCard = NULL;
    endCard = NULL;
    startPoint.set(0, 0);
    endPoint.set(0, 0);
    box = NULL;
    field = NULL;
    isMoving = false;
}
GameScene::~GameScene()
{
    chooseCard = NULL;
    endCard = NULL;
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
            log("%f,%f",(box->getContentSize().width / TileRow) * (j + 0.5),(box->getContentSize().height / TileHor) * (i + 0.5));
            gameTile[i][j]->setCoord(i,j);
            setPositionByCoor(gameTile[i][j]);
            
        }
        
    }
    
    //更换可以消除的card
    
    for (int i = 0 ; i < TileHor; i ++) {
        
        for (int j= 0 ; j < TileRow; j++) {
//            gameTile[i][j]->setCoord(Vec2(i, j));
            gameTile[i][j]->setCoord(i,j);
            while (checkIsCanPairUp(gameTile[i][j])) {
                GameType n = (GameType)createRandomValue((int)GameType_house, (int)GameType_traffic);
                
                gameTile[i][j]->changeCard(n, TypeLevel_1);
            }
        }
    }
    
}

bool GameScene::checkIsCanPairUp(CardSprite* card)
{
    if (pairUpVec.size() > 0) {
        pairUpVec.clear();
    }
    GameType type = gameTile[card->getCoord().hor][card->getCoord().row]->getType();
    TypeLevel _level = gameTile[card->getCoord().hor][card->getCoord().row]->getLevel();
    int count = 1;
    bool flag = false;
//    CCLOG("%d,%d,%d",card.hor,card.row,type);
    //上边
    for (int i = card->getCoord().hor + 1 ; i < TileHor; i ++) {
        if (type == gameTile[i][card->getCoord().row]->getType() && _level == gameTile[i][card->getCoord().row]->getLevel()) {
            count ++;
            pairUpVec.push_back(gameTile[i][card->getCoord().row]);
        }else{
            break;
        }
    }
    //下边
    for (int i = card->getCoord().hor - 1; i >= 0; i --) {
        if (type == gameTile[i][card->getCoord().row]->getType() && _level == gameTile[i][card->getCoord().row]->getLevel()) {
            count ++;
            pairUpVec.push_back(gameTile[i][card->getCoord().row]);
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
    for (int i = card->getCoord().row + 1; i < TileRow; i ++) {
        if (type == gameTile[card->getCoord().hor][i]->getType() && _level == gameTile[card->getCoord().hor][i]->getLevel()) {
            count ++;
            pairUpVec.push_back(gameTile[card->getCoord().hor][i]);
        }else{
            break;
        }
    }
    //左边
    for (int i = card->getCoord().row - 1; i >= 0; i --) {
        if (type == gameTile[card->getCoord().hor][i]->getType() && _level == gameTile[card->getCoord().hor][i]->getLevel()) {
            count ++;
            pairUpVec.push_back(gameTile[card->getCoord().hor][i]);
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
                chooseCard = gameTile[i][j];
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
    if (!chooseCard) {
        return;
    }

    Vec2 point = touch->getLocation();
    endPoint = point;
    float slideX = endPoint.x - startPoint.x;
    float slideY = endPoint.y - startPoint.y;
    gameTile[chooseCard->getCoord().hor][chooseCard->getCoord().row]->setScale(1.f);

    if (fabs(slideX) > fabs(slideY)) {
        
        if (slideX > 50) {
            
            if (chooseCard->getCoord().row < TileRow - 1) {
                exchangeCard(chooseCard, gameTile[chooseCard->getCoord().hor][chooseCard->getCoord().row + 1]);
            }
            
        }else if (slideX < -50){
            
            if (chooseCard->getCoord().row > 0) {
                exchangeCard(chooseCard, gameTile[chooseCard->getCoord().hor][chooseCard->getCoord().row - 1]);
            }
            
            
        }
        
        
    }else{
        
        if (slideY > 50) {
            
            if (chooseCard->getCoord().hor < TileHor - 1) {
                exchangeCard(chooseCard, gameTile[chooseCard->getCoord().hor + 1][chooseCard->getCoord().row]);

            }
            
        }else if (slideY < -50){
            
            if (chooseCard->getCoord().hor > 0) {
                exchangeCard(chooseCard, gameTile[chooseCard->getCoord().hor - 1][chooseCard->getCoord().row]);
            
            }
            
            
        }
        
    }
    
    
    
    if (box->getChildByName("mask")) {
        box->getChildByName("mask")->removeFromParent();
    }
    
    chooseCard = NULL;
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

void GameScene::exchangeCard(CardSprite* card1, CardSprite* card2)
{
    bool isPairUp = false;
    if (!isMoving) {
        log("moving");
        isMoving = true;
        ActionInterval* move1To2 = MoveTo::create(moveTime, gameTile[card2->getCoord().hor][card2->getCoord().row]->getPosition());
        ActionInterval* move2To1 = MoveTo::create(moveTime, gameTile[card1->getCoord().hor][card1->getCoord().row]->getPosition());
        gameTile[card1->getCoord().hor][card1->getCoord().row]->runAction(move1To2);
        gameTile[card2->getCoord().hor][card2->getCoord().row]->runAction(move2To1);
        
        CardSprite* temp = gameTile[card1->getCoord().hor][card1->getCoord().row];
        gameTile[card1->getCoord().hor][card1->getCoord().row] = gameTile[card2->getCoord().hor][card2->getCoord().row];
        gameTile[card2->getCoord().hor][card2->getCoord().row] = temp;
        
        
        if (checkIsCanPairUp(card1)) {
            for (int i = 0; i < pairUpVec.size() ; i ++) {
                CardSprite* _card = pairUpVec.at(i);
                gameTile[_card->getCoord().hor][_card->getCoord().row]->runAction(Sequence::create(MoveTo::create(moveTime, gameTile[card2->getCoord().hor][card2->getCoord().row]->getPosition()), CallFunc::create(CC_CALLBACK_0(GameScene::pairUpAndLevelUp, this, card2)), CallFunc::create(CC_CALLBACK_0(GameScene::endMoving, this)), NULL) );
            }
            isPairUp = true;
        }else{
            isPairUp = false;
        }
        
        if (checkIsCanPairUp(card2)) {
            for (int i = 0; i < pairUpVec.size() ; i ++) {
                CardSprite* _card = pairUpVec.at(i);
                gameTile[_card->getCoord().hor][_card->getCoord().row]->runAction(Sequence::create(MoveTo::create(moveTime, gameTile[card1->getCoord().hor][card1->getCoord().row]->getPosition()), CallFunc::create(CC_CALLBACK_0(GameScene::pairUpAndLevelUp, this,card2)), CallFunc::create(CC_CALLBACK_0(GameScene::endMoving, this)), NULL) );
            }
            isPairUp = true;
        }
        
        if (!isPairUp) {
            gameTile[card1->getCoord().hor][card1->getCoord().row]->runAction(Sequence::create(DelayTime::create(moveTime), move1To2, CallFunc::create(CC_CALLBACK_0(GameScene::endMoving, this)), NULL) );
            gameTile[card2->getCoord().hor][card2->getCoord().row]->runAction(Sequence::create(DelayTime::create(moveTime), move2To1, CallFunc::create(CC_CALLBACK_0(GameScene::endMoving, this)), NULL) );
            
            CardSprite* temp = gameTile[card1->getCoord().hor][card1->getCoord().row];
            gameTile[card1->getCoord().hor][card1->getCoord().row] = gameTile[card2->getCoord().hor][card2->getCoord().row];
            gameTile[card2->getCoord().hor][card2->getCoord().row] = temp;
            
        }
        
        
    }
}

void GameScene::endMoving()
{
    isMoving = false;
}

void GameScene::pairUpAndLevelUp(CardSprite* card)
{
    GameType _type = gameTile[card->getCoord().hor][card->getCoord().row]->getType();
    TypeLevel _level = gameTile[card->getCoord().hor][card->getCoord().row]->getLevel();
    if (_level < TypeLevel_5) {
        _level = (TypeLevel)((int)_level + 1);
    }
    gameTile[card->getCoord().hor][card->getCoord().row]->changeCard(_type, _level);
    
    for (int i = 0; i < pairUpVec.size() ; i ++) {
        CardSprite* _card = pairUpVec.at(i);
        gameTile[_card->getCoord().hor][_card->getCoord().row]->removeFromParent();
        gameTile[_card->getCoord().hor][_card->getCoord().row]->isPairUp = true;
    }
    
    setPositionByCoor(card);
    
    cardDrop();

}

void GameScene::cardDrop()
{

    for (int i = 0; i < pairUpVec.size() ; i ++) {
        CardSprite* _card = pairUpVec.at(i);
        for (int m = _card->getCoord().hor + 1 ; m < TileHor ; m ++) {
            if (!gameTile[m][_card->getCoord().row]->isPairUp) {
                gameTile[m - 1][_card->getCoord().row] = gameTile[m][_card->getCoord().row];
                gameTile[m - 1][_card->getCoord().row]->isPairUp = false;
                gameTile[m][_card->getCoord().row]->isPairUp = true;
                setPositionByCoor(gameTile[m - 1][_card->getCoord().row], true);
            }
        }
    }
    
}

//根据坐标设置位置
void GameScene::setPositionByCoor(CardSprite* card, bool isAction)
{
    if (isAction) {
        card->runAction(MoveTo::create(moveTime, Vec2((box->getContentSize().width / TileRow) * (card->getCoord().row + 0.5) ,((box->getContentSize().height - 60) / TileHor) * (card->getCoord().hor + 0.5) + 5)));
//        gameTile[i][j]->setMyPosition(Vec2((box->getContentSize().width / TileRow) * (j + 0.5) ,((box->getContentSize().height - 60) / TileHor) * (i + 0.5) + 5));
    }else{
        card->setPosition(Vec2((box->getContentSize().width / TileRow) * (card->getCoord().row + 0.5) ,((box->getContentSize().height - 60) / TileHor) * (card->getCoord().hor + 0.5) + 5));
//        gameTile[i][j]->setMyPosition(Vec2((box->getContentSize().width / TileRow) * (j + 0.5) ,((box->getContentSize().height - 60) / TileHor) * (i + 0.5) + 5));
    }
    
}
