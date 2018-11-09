//
//  HUBLayer.cpp
//  AirHockey
//
//  Created by VietCT on 10/17/16.
//
//

#include "HUBLayer.hpp"
#include "SimpleAudioEngine.h"
#include "GamePlayScene.hpp"


USING_NS_CC;

bool HUBLayer::init()
{
    if(!Layer::init()) return false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_sheet.plist");
    visibleSize = Director::getInstance()->getVisibleSize();
    scoreLabel();
    otherLabel();
    isPaused = false;
    return true;
}

void HUBLayer::scoreLabel()
{
    label1 = Label::createWithBMFont("font.fnt", "0");
    label1->setPosition(Vec2(visibleSize.width/2,
                             visibleSize.height - label1->getContentSize().height));
	label2 = Label::createWithBMFont("font.fnt", "100");
    label2->setPosition(Vec2(label2->getContentSize().width*2,
                             visibleSize.height - label1->getContentSize().height));

    this->addChild(label1);
	this->addChild(label2);
}

void HUBLayer::otherLabel()
{
	auto healthIcon = Sprite::createWithSpriteFrameName("health_icon.png");
	healthIcon->setPosition(label2->getPositionX() - healthIcon->getContentSize().width,
							label2->getPositionY());
	this->addChild(healthIcon);
    soundButton = ui::CheckBox::create("_bookgame_UI_soundON.png", "_bookgame_UI_soundOFF.png");
    soundButton->setPosition(Vec2(visibleSize.width/2 + soundButton->getContentSize().width,
									visibleSize.height/2));
    soundButton->addEventListener(CC_CALLBACK_2(HUBLayer::changeSound, this));
	soundButton->setScale(0.8f);
    this->addChild(soundButton,1);
    soundButton->setVisible(false);
    
    optionButton = MenuItemImage::create("_bookgame_UI_options.png", "_bookgame_UI_options.png",
                                         CC_CALLBACK_0(HUBLayer::callOptionLayer, this));
    optionButton->setScale(0.5f);
    optionButton->setPosition(visibleSize.width - optionButton->getContentSize().width*0.5f,
		visibleSize.height-optionButton->getContentSize().height*0.5f);
    
    resumeButton = MenuItemImage::create("_bookgame_UI_resume.png","_bookgame_UI_resume.png",
                                       CC_CALLBACK_0(HUBLayer::callBackGamePlay, this));
    resumeButton->setPosition(Vec2(visibleSize.width/2 - resumeButton->getContentSize().width,
								visibleSize.height/2));
	resumeButton->setScale(0.8f);
    resumeButton->setVisible(false);
    
    auto menu = Menu::create(optionButton,resumeButton,nullptr);
    menu->setPosition(Vec2(0,0));
    this->addChild(menu,1);
}

void HUBLayer::changeSound(Ref* sender, ui::CheckBox::EventType type)
{
    switch (type) {
        case ui::CheckBox::EventType::SELECTED:
            //UserDefault::getInstance()->setBoolForKey("isSoundPaused", true);
            //CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
            break;
        case ui::CheckBox::EventType::UNSELECTED:
            //CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
            break;
        default:
            break;
    }
}


void HUBLayer::callOptionLayer()
{
    auto playScene = (GamePlayScene*)this->getParent();
    playScene->unscheduleUpdate();
    optionButton->setVisible(false);
    resumeButton->setVisible(true);
    soundButton->setVisible(true);
    isPaused = true;
}

void HUBLayer::callBackGamePlay()
{
    auto playScene = (GamePlayScene*)this->getParent();
    playScene->scheduleUpdate();
    optionButton->setVisible(true);
    resumeButton->setVisible(false);
    soundButton->setVisible(false);
    isPaused = false;
}

void HUBLayer::update(int s1, int hp)
{
    char c1[5]{};
    sprintf(c1, "%d",s1);
    
    label1->setString(c1);

	char c2[5]{};
    sprintf(c2, "%d",hp);
    
    label1->setString(c2);
}