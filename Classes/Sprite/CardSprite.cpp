//
//  CardSprite.cpp
//  kindomPairUp
//
//  Created by Jiyao on 14/11/16.
//
//

#include "CardSprite.h"

CardSprite::CardSprite()
{
    m_Type = GameType_NULL;
    m_Level = TypeLevel_NULL;
    m_Coord = Vec2(0, 0);
    isPairUp = false;
}
CardSprite::~CardSprite()
{
    m_Type = GameType_NULL;
    m_Level = TypeLevel_NULL;
    m_Coord = Vec2(0, 0);
    isPairUp = true;
}

void CardSprite::initWithTypeAndLevel(GameType _type, TypeLevel _level)
{
    
    char _name[1024];
    sprintf(_name, "iphone/GameScene/card/card_%02d.png",(int)_type);
    this->initWithFile(_name);
    
    sprintf(_name, "iphone/GameScene/card/card_%02d_%02d.png",(int)_type, (int)_level);
    Sprite* m_sprite = Sprite::create(_name);
    this->addChild(m_sprite);
    m_sprite->setName("thing");
    
    m_sprite->setPosition(Vec2(this->getContentSize().width / 2 , this->getContentSize().height / 2));
    
    
    setType(_type);
    setLevel(_level);
}

void CardSprite::changeCard(GameType _type, TypeLevel _level)
{
    char _name[1024];
    sprintf(_name, "iphone/GameScene/card/card_%02d.png",(int)_type);
    this->setTexture(_name);
    
    sprintf(_name, "iphone/GameScene/card/card_%02d_%02d.png",(int)_type, (int)_level);
    Sprite* m_sprite = (Sprite*)this->getChildByName("thing");
    m_sprite->setTexture(_name);
    
    setType(_type);
    setLevel(_level);
}

void CardSprite::moveCard(Vec2 coord){
    
    
    
}
