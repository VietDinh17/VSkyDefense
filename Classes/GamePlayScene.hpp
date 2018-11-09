//
//  GamePlayScene.hpp
//  VSkyDefense
//
//  Created by VietCT on 11/2/16.
//
//

#ifndef GamePlayScene_hpp
#define GamePlayScene_hpp

#include <cocos2d.h>
#include "Explode.hpp"
#include "HUBLayer.hpp"
#include "FallingObject.h"


enum class Order
{
    kBackground = 1,
    kMiddleground,
    kForeground,
};

class GamePlayScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    void update(float dt) override;
    
private:
    cocos2d::Size visibleSize;
    bool isFirstTap;
    Explode* explode;
	HUBLayer* hub;
	cocos2d::Vector<FallingObject*> meteors;
	float _destroyHeight;
	float _time;
private:
    CREATE_FUNC(GamePlayScene);
    
    bool init() override;

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
    
    void backGroundInit(bool b);

	void createShockwave();

	void spawnMeteor(float dt);

	void spawnBackGrMeteor(float t);
};





#endif /* GamePlayScene_hpp */
