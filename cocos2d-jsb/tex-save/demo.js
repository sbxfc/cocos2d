var HelloWorldLayer = cc.Layer.extend({
    sprite: null,
    ctor: function () {
        this._super();

        if (cc.sys.isNative) {
            var writablePath = jsb.fileUtils.getWritablePath();
            jsb.fileUtils.addSearchPath(writablePath);

            //从本地读取一张图片
            var sprite = new cc.Sprite();
            sprite.initWithFile("res/HelloWorld.png");
            var texture = sprite.getTexture();
            cc.log("texture->w:" + texture.width + "h:" + texture.height);

            //将纹理保存到本地
            var rt = cc.RenderTexture(texture.width, texture.height);
            rt.begin();
            var sprite = new cc.Sprite();
            sprite.initWithTexture(texture);
            sprite.retain();
            sprite.setAnchorPoint(0, 0);
            sprite.setPosition(0, 0);
            sprite.visit();
            sprite.release();
            rt.end();

            jsb.fileUtils.createDirectory(writablePath + "/res/Image")
            rt.saveToFile("res/Image/sbxfc.png", true);

            //add scheduler
            this.scheduleUpdate();
        }

        return true;
    },
    update: function (delay) {
        var writablePath = jsb.fileUtils.getWritablePath();
        var filePath = writablePath + "res/Image/sbxfc.png";
        if (jsb.fileUtils.isFileExist(filePath)) {
            //读取本地图片
            var winSize = cc.director.getWinSize();
            var sprite = new cc.Sprite();
            sprite.initWithFile("res/Image/sbxfc.png");
            sprite.setPosition(winSize.width * 0.5, winSize.height * 0.5);
            this.addChild(sprite);

            //remove scheduler
            this.unscheduleUpdate();
        }
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter: function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

