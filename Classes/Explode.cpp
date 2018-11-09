//
//  Explode.cpp
//  VSkyDefense
//
//  Created by VietCT on 11/11/16.
//
//

#include "Explode.hpp"

USING_NS_CC;

#define MINIMUM_BOOM_SCALE 0.425

Explode::Explode(Vec2 pos)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 posRing{visibleSize.width*0.05f,visibleSize.height*0.10f};
	Vec2 posSparkle{visibleSize.width*0.09f,visibleSize.height*0.17f};

    boom = BiggerSprite::createWithPos("bomb.png", pos);
	auto outterRing = BiggerSprite::createWithPos("halo.png", posRing);
	outterRing->setScale(0.7);
	auto sparkle = BiggerSprite::createWithPos("sparkle.png", posSparkle);
	sparkle->setScale(0.67);
    
	this->addChild(boom,1);
	boom->addChild(outterRing,1);
	boom->addChild(sparkle, 1);
    boom->growing();
    outterRing->rotate();
	sparkle->rotate();

}

bool Explode::isOverMinimumSize() const
{
	if (boomScale() < MINIMUM_BOOM_SCALE) return false;
	return true;
}




