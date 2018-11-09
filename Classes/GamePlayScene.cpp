//
//  GamePlayScene.cpp
//  VSkyDefense
//
//  Created by VietCT on 11/2/16.
//
//

#include "GamePlayScene.hpp"
#include "BiggerSprite.hpp"


USING_NS_CC;

#define METEOR_TIME_INTERVAL 2.0

Scene* GamePlayScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GamePlayScene::create();
    
    scene->addChild(layer);
    
    return scene;
}


bool GamePlayScene::init()
{
    if(!Layer::init()) return false;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    isFirstTap = true;

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_sheet.plist");
    backGroundInit(true);
	_destroyHeight = this->getChildByName("cityDark")->getContentSize().height;

	hub = HUBLayer::create();
	this->addChild(hub, (int)Order::kForeground);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GamePlayScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //create main loop
    this->scheduleUpdate();
	this->schedule(schedule_selector(GamePlayScene::spawnMeteor), 4);
    
    return true;
}

void GamePlayScene::update(float dt)
{
	_time += dt;
	if (_time >= METEOR_TIME_INTERVAL)
	{
		spawnBackGrMeteor(_time);
		_time = 0;
	}
}

void GamePlayScene::spawnBackGrMeteor(float t)
{
	auto bgMeteor = FallingObject::create("meteor.png",_destroyHeight);
	bgMeteor->setScale(t*0.25);
	bgMeteor->setOpacity(50.0f);
	bgMeteor->setColor(Color3B::BLUE);
	this->addChild(bgMeteor, (int)Order::kBackground - 2);
	bgMeteor->fallingAction(t);
}

void GamePlayScene::spawnMeteor(float dt)
{
	auto meteor = FallingObject::create("meteor.png",_destroyHeight);
	this->addChild(meteor, (int)Order::kMiddleground+1);
	meteor->fallingAction(3.5);
	meteors.pushBack(meteor);
}

void GamePlayScene::backGroundInit(bool b)
{
    if(b)
    {
        auto bG = Sprite::create("bg.png");
        bG->setPosition(visibleSize.width/2, visibleSize.height/2);
        this->addChild(bG,(int)Order::kBackground-3);
        
        for(int i = 0; i < 2; ++i)
        {
            auto cityDark = Sprite::createWithSpriteFrameName("city_dark.png");
            cityDark->setPosition(cityDark->getContentSize().width/2 + i*visibleSize.width/2,
                                  cityDark->getContentSize().height/2);
            this->addChild(cityDark,(int)Order::kBackground-1,"cityDark");
            
            auto cityLight = Sprite::createWithSpriteFrameName("city_light.png");
            cityLight->setPosition(cityLight->getContentSize().width/2+ i*visibleSize.width*0.5 + 20,
                                   cityLight->getContentSize().height*0.9);
            this->addChild(cityLight,(int)Order::kBackground-2);
        }
        for(int i = 0; i < 4; ++i )
        {
            auto tree = Sprite::createWithSpriteFrameName("trees.png");
            tree->setPosition(tree->getContentSize().width/2+ i*visibleSize.width/4,
                              tree->getContentSize().height/2);
            this->addChild(tree,(int)Order::kBackground);
        }
        
    }
}

bool GamePlayScene::onTouchBegan(Touch* touch, Event* event)
{
    if(!hub->isPaused)
	{ 
		if(touch)
		{
			if(isFirstTap)
			{
				Vec2 tap = touch->getLocation();
				explode = new Explode(tap);
				this->addChild(explode, (int)Order::kMiddleground);	
				isFirstTap = false;
			}else{
				isFirstTap = true;
				createShockwave();	
				this->removeChild(explode);
				explode->release();
			}
		}
	}
    
    return false;
    
}

void GamePlayScene::createShockwave()
{
	if(explode->isOverMinimumSize())
	{ 
		auto shockwave = BiggerSprite::createWithPos("shockwave.png", explode->boomPos());
		this->addChild(shockwave);
		shockwave->fadeOut(explode->boomScale());
	}		
}

