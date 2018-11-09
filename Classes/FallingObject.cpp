#include "FallingObject.h"


USING_NS_CC;

FallingObject *FallingObject::create(const char* name, float y)
{
	auto sprite = new FallingObject(y);
    if(sprite && sprite->init(name))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return sprite = nullptr;
}

void FallingObject::fallingAction(float t)
{
	xTarget = RandomHelper::random_real(0.0f, visibleSize.width);
	if (xTarget <= _radius) xTarget += _radius;
	if (xTarget >= visibleSize.width - _radius) xTarget -= _radius;
	auto moveTo = MoveTo::create(timeToFall(t), Vec2(xTarget, _yTarget));
	this->runAction(Sequence::create(moveTo,
		CallFuncN::create(std::bind(&FallingObject::removeFromParent,this)),nullptr));
}

bool FallingObject::init(const char* name)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_sheet.plist");
	float rangeXstart = visibleSize.width / 7;
	xPos = RandomHelper::random_real(rangeXstart,visibleSize.width-rangeXstart);
	if(!imageInit(name)) return false;	
	return true;
}

bool FallingObject::imageInit(const char* name)
{
	this->initWithSpriteFrameName(name);
	_radius = this->getContentSize().width/2;
	this->setPosition(Vec2(xPos, visibleSize.height+_radius));
	return true;
}

float FallingObject::timeToFall(float t)
{
	float distance = visibleSize.height - _yTarget;
	float speed =  distance / t;
	float r = pow(abs(xPos - xTarget), 2) + pow(distance, 2);
	float time = sqrt(r) / speed;
	return time;
}


