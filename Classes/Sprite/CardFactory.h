//
//  CardFactory.h
//  kindomPairUp
//
//  Created by Jiyao on 14/11/15.
//
//

#ifndef __kindomPairUp__CardFactory__
#define __kindomPairUp__CardFactory__

#include "cocos2d.h"
#include "Global.h"
#include "CardSprite.h"

USING_NS_CC;
class CardFactory : public Sprite {
    
public:
    
    static CardSprite* getCard(GameType _type, TypeLevel _level);
    
private:
    
};

#endif /* defined(__kindomPairUp__CardFactory__) */
