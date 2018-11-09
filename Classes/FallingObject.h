#ifndef __FALLING__OBJECT__
#define __FALLING__OBJECT__

#include "cocos2d.h"



class FallingObject : public cocos2d::Sprite
{
public:
	static FallingObject* create(const char* name, float yTarget);
	float radius() const { return _radius; }
	void fallingAction(float time);
	void setDestroyHeight(float yTarget) { _yTarget = yTarget; }

private:
	cocos2d::Size visibleSize;
	float _yTarget;
	float xTarget;
	float xPos;
	float _radius;


private:
	FallingObject(float yTarget) : _yTarget{yTarget}{}
	bool init(const char* name);
	bool imageInit(const char* name);
	float timeToFall(float t);
};





#endif //!__FALLINF__OBJECT__
