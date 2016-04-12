#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "AppMacros.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
   

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        //glview->setFrameSize(480, 320);	// 在这里设置创建窗口的尺寸，手机上这个就不用啦，因为手机有固定的屏幕
        glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::FIXED_HEIGHT);
        director->setOpenGLView(glview);
    }
    
    auto screenSize = glview->getFrameSize();	// 获取屏幕尺寸
    std::vector<std::string> searchPaths;
    
    // 这里是实现的重点，比较屏幕的高和设定的三种适配尺寸的高，选择合适的图片
    // 然后将对应图片的路径添加到搜索路径中，那么cocos2d-x就会到该目录去寻找图片
    if (screenSize.height > mediumResource.size.height){
        searchPaths.push_back(largeResource.directory);
    }
    else if (screenSize.height > smallResource.size.height){
        searchPaths.push_back(mediumResource.directory);
    }
    else{
        searchPaths.push_back(smallResource.directory);
    }
    
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();
    
    // run
    director->runWithScene(scene);
    
    return true;
    
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
