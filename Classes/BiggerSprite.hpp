//
//  BiggerSprite.hpp
//  AirHockey
//
//  Created by VietCT on 10/14/16.
//
//

#ifndef MainSprite_hpp
#define MainSprite_hpp

#include <cocos2d.h>

class BiggerSprite : public cocos2d::Sprite
{
public:
    cocos2d::Vec2 initalPosition;
    
public:
    static BiggerSprite* createWithPos(const char* name, cocos2d::Vec2 position);
    void growing();
    void rotate();
    void fadeOut(float s);
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 position;
    
private:
    BiggerSprite(cocos2d::Vec2 p) : position{p}{}
    bool init(const char* name);

    
};

#endif /* MainSprite_hpp */
