#include "HelloWorldScene.h"
////////////////////////////////////////////////////////////////
#include <spine/SpineBatchNode.h>
using namespace spine;
////////////////////////////////////////////////////////////////
USING_NS_CC;

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

////////////////////////////////////////////////////////////////
    
    auto spineBatch = SpineBatchNode::create();
    spineBatch->setPosition(0, 0);
    addChild(spineBatch);
    
    SkeletonAnimation* skeletonNode;
    for (int i = 1; i <= 5; i ++) {
        skeletonNode = SkeletonAnimation::createWithFile("common/bat.json", "common/bat.atlas", 0.6f);
        skeletonNode->setAnimation(0, "idle", true);
        skeletonNode->setPosition(Vec2(100 + 45*(i%17), 60*(i%8) + 80));
        spineBatch->addChild(skeletonNode);
    }
    
////////////////////////////////////////////////////////////////
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
