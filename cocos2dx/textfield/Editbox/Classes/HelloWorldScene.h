#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class HelloWorld : public cocos2d::Layer, public EditBoxDelegate
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

private:
    virtual void editBoxEditingDidBegin(EditBox *editBox) override;
    virtual void editBoxEditingDidEnd(EditBox *editBox) override;
    virtual void editBoxTextChanged(EditBox *editBox, const std::string& text) override;
    virtual void editBoxReturn(EditBox *editBox) override;
};

#endif // __HELLOWORLD_SCENE_H__
