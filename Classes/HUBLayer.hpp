//
//  HUBLayer.hpp
//  AirHockey
//
//  Created by VietCT on 10/17/16.
//
//

#ifndef HUBLayer_hpp
#define HUBLayer_hpp

#include <cocos2d.h>
#include "ui/CocosGUI.h"


class HUBLayer : public cocos2d::Layer
{
public:
    bool isPaused;
public:
    CREATE_FUNC(HUBLayer);
    void update(int score, int hp);
    
    
private:
    cocos2d::Label* label1;
	cocos2d::Label* label2;
    cocos2d::Size visibleSize;
    cocos2d::ui::CheckBox* soundButton;
    cocos2d::MenuItemImage* optionButton;
    cocos2d::MenuItemImage* resumeButton;
   
    
private:
    bool init() override;
    void scoreLabel();
    void otherLabel();
    void callOptionLayer();
    void callBackGamePlay();
    void changeSound(cocos2d::Ref*, cocos2d::ui::CheckBox::EventType );
    
    
};

#endif /* HUBLayer_hpp */
