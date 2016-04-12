
/*
 * 大部分内容是Cocos2d-x 3.8.1 
 * tests/cpp-tests/Classes/TextInputTest实例中的代码。
 */

#include "HelloWorldScene.h"

USING_NS_CC;

#define FONT_NAME                       "fonts/Thonburi.ttf"
#define FONT_SIZE                       48

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    
    
    auto editBox = EditBox::create(Size(686, 80), Scale9Sprite::create("InputBkg.png"));
    editBox->setFont(FONT_NAME, FONT_SIZE);
    editBox->setPosition(Vec2(winSize.width*0.5,winSize.height*0.75));
    editBox->setPlaceHolder("<click here for input>");
    editBox->setPlaceholderFontColor(Color3B::WHITE);
    editBox->setFontColor(Color3B::WHITE);
    editBox->setMaxLength(100);
    editBox->setText("<click here for input>");
    editBox->setReturnType(EditBox::KeyboardReturnType::DONE);
    editBox->setInputMode(EditBox::InputMode::ANY);
    editBox->setDelegate(this);
    this->addChild(editBox);
    
    return true;
}

#pragma mark - EditBoxDelegate
void HelloWorld::editBoxEditingDidBegin(EditBox *editBox) {
}

void HelloWorld::editBoxEditingDidEnd(EditBox *editBox) {
}

void HelloWorld::editBoxTextChanged(EditBox *editBox, const std::string& text) {
}

void HelloWorld::editBoxReturn(EditBox *editBox) {
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
