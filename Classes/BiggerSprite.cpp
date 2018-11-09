//
//  BiggerSprite.cpp
//  AirHockey
//
//  Created by VietCT on 10/14/16.
//
//

#include "BiggerSprite.hpp"

#define SHOCKWAVE_SPEED 1.54

USING_NS_CC;

BiggerSprite* BiggerSprite::createWithPos(const char* name, Vec2 p)
{
    auto sprite = new BiggerSprite(p);
    if(sprite && sprite->init(name))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return sprite = nullptr;
}


bool BiggerSprite::init(const char* name)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_sheet.plist");
    this->initWithSpriteFrameName(name);
    this->setPosition(position);
    this->setScale(0.1);
    return true;
}


void BiggerSprite::growing()
{
	this->setOpacity(40.0f);
	auto fadeInt = FadeIn::create(2.0f);
    auto scaleTo = ScaleTo::create(2.0f, 1.0f);
    this->runAction(Spawn::create(scaleTo,fadeInt,nullptr));
}

void BiggerSprite::rotate()
{
	this->setOpacity(40.0f);
	auto fadeInt = FadeIn::create(2.0f);
    auto rotate = RotateBy::create(0.5f, -90.0f);
	this->runAction(fadeInt);
    this->runAction(RepeatForever::create(rotate));
}

void BiggerSprite::fadeOut(float s)
{
	float time = s / SHOCKWAVE_SPEED;
    auto scaleTo = ScaleTo::create(time, s);
    auto fadeout = FadeOut::create(time*1.38f);
	auto delay = DelayTime::create(time*1.38f);
    this->runAction(Sequence::create(Spawn::create(scaleTo,fadeout,nullptr),
		CallFuncN::create(std::bind(&BiggerSprite::removeFromParent,this)
		),nullptr));
}


