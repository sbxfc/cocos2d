
#cocos2d-jsb

不修改引擎源码的情况下,通过cc.RenderTexture将纹理保存至本地。

由于RenderTexture.saveToFile使用了异步模式,所以用到了一个scheduler来判断图片已经保存完成。

代码量很小。  :-)




