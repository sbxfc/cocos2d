
/*
 * 大部分内容是Cocos2d-x 3.8.1 
 * tests/cpp-tests/Classes/TextInputTest实例中的代码。
 */

#include "HelloWorldScene.h"

USING_NS_CC;

#define FONT_NAME                       "fonts/Thonburi.ttf"
#define FONT_SIZE                       72

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
    
    _charLimit = 12;
    
    //创建文本框
    auto pTextField = TextFieldTTF::textFieldWithPlaceHolder("<click here for input>",FONT_NAME,FONT_SIZE);
    pTextField->setPosition(Vec2(winSize.width *0.5, winSize.height*0.75));
    addChild(pTextField);
    //设置代理
    pTextField->setDelegate(this);
    
    //监听输入框点击事件
    addTextFieldTouchListener(pTextField);
    
    return true;
}

void HelloWorld::addTextFieldTouchListener(TextFieldTTF* pTextField){
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(false);
    touchListener->onTouchBegan = [](Touch* touch, Event* event) -> bool {
        
        // 获取事件所绑定的 target
        auto target = static_cast<Node*>(event->getCurrentTarget());
        
        // 获取当前点击点所在相对按钮的位置坐标
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        
        // 点击范围判断检测
        if (rect.containsPoint(locationInNode))
        {
            log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
            TextFieldTTF* textfield = (TextFieldTTF*)target;
            textfield->attachWithIME();
            return true;
        }
        return false;
    };
    
    touchListener->onTouchMoved = [](Touch* touch, Event* event){
        
    };
    
    // 点击事件结束处理
    touchListener->onTouchEnded = [=](Touch* touch, Event* event){
        
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,pTextField);
}

void HelloWorld::callbackRemoveNodeWhenDidAction(Node * node)
{
    this->removeChild(node, true);
}

// TextFieldDelegate protocol
bool HelloWorld::onTextFieldAttachWithIME(TextFieldTTF * sender)
{
    return false;
}

bool HelloWorld::onTextFieldDetachWithIME(TextFieldTTF * sender)
{
    return false;
}

bool HelloWorld::onTextFieldInsertText(TextFieldTTF * sender, const char * text, size_t nLen)
{
    // if insert enter, treat as default to detach with ime
    if ('\n' == *text)
    {
        return false;
    }
    
    // if the textfield's char count more than _charLimit, doesn't insert text anymore.
    if (sender->getCharCount() >= _charLimit)
    {
        return true;
    }
    
    // create a insert text sprite and do some action
    auto label = Label::createWithSystemFont(text, FONT_NAME, FONT_SIZE);
    this->addChild(label);
    Color3B color(226, 121, 7);
    label->setColor(color);
    
    // move the sprite from top to position
    auto endPos = sender->getPosition();
    if (sender->getCharCount())
    {
        endPos.x += sender->getContentSize().width / 2;
    }
    auto inputTextSize = label->getContentSize();
    Vec2 beginPos(endPos.x, Director::getInstance()->getWinSize().height - inputTextSize.height * 2);
    
    float duration = 0.5;
    label->setPosition(beginPos);
    label->setScale(8);
    
    auto seq = Sequence::create(
                                Spawn::create(
                                              MoveTo::create(duration, endPos),
                                              ScaleTo::create(duration, 1),
                                              FadeOut::create(duration),
                                              nullptr),
                                CallFuncN::create(CC_CALLBACK_1(HelloWorld::callbackRemoveNodeWhenDidAction, this)),
                                nullptr);
    label->runAction(seq);
    
    return false;
}

bool HelloWorld::onTextFieldDeleteBackward(TextFieldTTF * sender, const char * delText, size_t nLen)
{
    // create a delete text sprite and do some action
    auto label = Label::createWithSystemFont(delText, FONT_NAME, FONT_SIZE);
    this->addChild(label);
    
    // move the sprite to fly out
    auto beginPos = sender->getPosition();
    auto textfieldSize = sender->getContentSize();
    auto labelSize = label->getContentSize();
    beginPos.x += (textfieldSize.width - labelSize.width) / 2.0f;
    
    auto winSize = Director::getInstance()->getWinSize();
    Vec2 endPos(- winSize.width / 4.0f, winSize.height * (0.5 + (float)rand() / (2.0f * RAND_MAX)));
    
    float duration = 1;
    float rotateDuration = 0.2f;
    int repeatTime = 5;
    label->setPosition(beginPos);
    
    auto seq = Sequence::create(
                                Spawn::create(
                                              MoveTo::create(duration, endPos),
                                              Repeat::create(
                                                             RotateBy::create(rotateDuration, (rand()%2) ? 360 : -360),
                                                             repeatTime),
                                              FadeOut::create(duration),
                                              nullptr),
                                CallFuncN::create(CC_CALLBACK_1(HelloWorld::callbackRemoveNodeWhenDidAction, this)),
                                nullptr);
    label->runAction(seq);
    return false;
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
