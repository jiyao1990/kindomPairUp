//
//  CardFactory.cpp
//  kindomPairUp
//
//  Created by Jiyao on 14/11/15.
//
//

#include "CardFactory.h"


CardSprite* CardFactory::getCard(GameType _type, TypeLevel _level)
{
    
    CardSprite* card = new CardSprite();
    card->initWithTypeAndLevel(_type, _level);
    
//    Node* node = Node::create();
//    node->addChild(card);
    
    return card;
    
}