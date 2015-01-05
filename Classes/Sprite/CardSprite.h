//
//  CardSprite.h
//  kindomPairUp
//
//  Created by Jiyao on 14/11/16.
//
//

#ifndef __kindomPairUp__CardSprite__
#define __kindomPairUp__CardSprite__

#include "cocos2d.h"
#include "Global.h"

USING_NS_CC;
class CardSprite : public Sprite {
    
public:
    CardSprite();
    ~CardSprite();
//    static Sprite* create(GameType _type, TypeLevel _level);
    void initWithTypeAndLevel(GameType _type, TypeLevel _level);
    
    void changeCard(GameType _type, TypeLevel _level);
    
    void moveCard(Vec2 coord);
    
    
    CC_SYNTHESIZE(GameType, m_Type, Type);
    CC_SYNTHESIZE(TypeLevel, m_Level, Level);
//    CC_SYNTHESIZE(Point, m_Position, MyPosition);
    CC_SYNTHESIZE(Vec2, m_Coord, Coord);
    
    bool isPairUp;
    
private:
    

    
};

#endif /* defined(__kindomPairUp__CardSprite__) */
