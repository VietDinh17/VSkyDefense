//
//  Explode.hpp
//  VSkyDefense
//
//  Created by VietCT on 11/11/16.
//
//

#ifndef Explode_hpp
#define Explode_hpp

#include <cocos2d.h>
#include "BiggerSprite.hpp"

class Explode : public cocos2d::Node
{
public:
    Explode(cocos2d::Vec2 p);
	float boomScale() const { return boom->getScale(); }
	cocos2d::Vec2 boomPos() const { return boom->getPosition(); }
	bool isOverMinimumSize() const;
    
private:
    BiggerSprite* boom;
    
private:

};


#endif /* Explode_hpp */
