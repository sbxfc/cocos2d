//
//  GameLoadingScene.cpp
//  AddImageAsync
//
//  Created by sbx_fc on 15/12/1.
//
//

#include "GameLoadingScene.h"
#include "HelloWorldScene.h"

Scene* GameLoadingScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameLoadingScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameLoadingScene::init()
{
    Layer::init();
    
    auto winSize = Director::getInstance()->getWinSize();
    
    mTextureNum = 0;
    int *pTextureNum = &mTextureNum;
    
    auto label = Label::createWithSystemFont("Loading...", "Arial", 36);
    label->setPosition(winSize.width / 2, winSize.height / 2);
    addChild(label);
    
    auto addImageCallback = [pTextureNum](Texture2D* texture)
    {
        (*pTextureNum)++;
        log("Load a texture async");
    };
    
    
    Director::getInstance()->getTextureCache()->addImageAsync("HelloWorld.png", addImageCallback);
    Director::getInstance()->getTextureCache()->addImageAsync("CloseSelected.png", addImageCallback);
    Director::getInstance()->getTextureCache()->addImageAsync("CloseNormal.png", addImageCallback);
    this->schedule(schedule_selector(GameLoadingScene::onTextureLoading));
    
    return true;
}

void GameLoadingScene::onTextureLoading(float dt)
{
    if (mTextureNum == 3){
        this->unschedule(schedule_selector(GameLoadingScene::onTextureLoading));
        log("Download Succ!");
        
        auto call = CallFunc::create([this](){
            auto scene = HelloWorld::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
        });
        this->runAction(Sequence::create(DelayTime::create(0.5), call, nullptr));
    }
}
