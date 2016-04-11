//
//  GameLoadingScene.hpp
//  AddImageAsync
//
//  Created by sbx_fc on 15/12/1.
//
//

#ifndef GameLoadingScene_hpp
#define GameLoadingScene_hpp

#include "cocos2d.h"

USING_NS_CC;

class GameLoadingScene : public Layer
{
public:
    static Scene* createScene();
    CREATE_FUNC(GameLoadingScene);
    bool init();
    
private:
    int mTextureNum;
    void onTextureLoading(float dt);
    
};

#endif /* GameLoadingScene_hpp */
