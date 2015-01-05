//
//  topSprite.cpp
//  kindomPairUp
//
//  Created by Jiyao on 14/11/9.
//
//

#include "TopSprite.h"

Sprite* TopSprite::m_sprite = NULL;

Sprite* TopSprite::create(GameType _type, TypeLevel _level)
{
 
    char _name[1024];
    sprintf(_name, "iphone/GameScene/top/top_%02d_%02d.png",(int)_type, (int)_level);
//    log(_name);
    m_sprite = Sprite::create(_name);
    return m_sprite;
}