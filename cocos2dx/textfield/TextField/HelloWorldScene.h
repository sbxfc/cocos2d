#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer,public cocos2d::TextFieldDelegate
{
    int _charLimit;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void addTextFieldTouchListener(cocos2d::TextFieldTTF* pTextField);
    
    void callbackRemoveNodeWhenDidAction(Node * node);

    // TextFieldDelegate
    virtual bool onTextFieldAttachWithIME(cocos2d::TextFieldTTF* sender) override;
    virtual bool onTextFieldDetachWithIME(cocos2d::TextFieldTTF* sender) override;
    virtual bool onTextFieldInsertText(cocos2d::TextFieldTTF* sender, const char* text, size_t nLen) override;
    virtual bool onTextFieldDeleteBackward(cocos2d::TextFieldTTF*  sender, const char * delText, size_t nLen) override;

};

#endif // __HELLOWORLD_SCENE_H__
