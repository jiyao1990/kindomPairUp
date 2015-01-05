//
//  TopSprite.h
//  kindomPairUp
//
//  Created by Jiyao on 14/11/9.
//
//

#ifndef __kindomPairUp__TopSprite__
#define __kindomPairUp__TopSprite__

#include "cocos2d.h"
#include "Global.h"

USING_NS_CC;
class TopSprite : public Sprite {
    
public:
    
    static Sprite* create(GameType _type, TypeLevel _level);

private:
    
    static Sprite* m_sprite;
};

#endif /* defined(__kindomPairUp__TopSprite__) */
