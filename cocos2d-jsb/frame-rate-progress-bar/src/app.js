var HelloWorldLayer = cc.Layer.extend({
    sprite: null,
    ctor: function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        var winSize = cc.winSize;

        var recordBtn = new ccui.Button();
        recordBtn.setAnchorPoint(0.5, 0.5);
        recordBtn.setPosition(winSize.width / 2, winSize.height / 2 - 100);
        recordBtn.setTitleText("Touch me!");
        recordBtn.setTitleFontSize(26);
        recordBtn.setContentSize(cc.size(150, 80));
        this.addChild(recordBtn);
        recordBtn.addClickEventListener(function () {

            var duration = 0.4; //花费时间
            var fromValue = 0;  //开始进度
            var toValue = 100;  //结束进度
            var PROGRESS_BAR_SIZE = cc.size(341, 32);//进度条尺寸
            var position = cc.p((winSize.width - PROGRESS_BAR_SIZE.width) / 2, winSize.height / 2);

            var bg = new ccui.ImageView();
            bg.loadTexture("res/img_progress_bg.png");
            bg.ignoreContentAdaptWithSize(false);
            bg.setAnchorPoint(0, 0.5);
            bg.setPosition((winSize.width - PROGRESS_BAR_SIZE.width) / 2, winSize.height / 2);
            bg.setContentSize(PROGRESS_BAR_SIZE);
            this.addChild(bg);

            var clipper = new cc.ClippingNode();
            clipper.setAnchorPoint(0, 0.5);
            clipper.setPosition(position);
            var stencil = new cc.DrawNode();
            var rect = [cc.p(0, -0.5 * PROGRESS_BAR_SIZE.height),                //左下
                cc.p(PROGRESS_BAR_SIZE.width * fromValue * 0.01, -0.5 * PROGRESS_BAR_SIZE.height),//右下
                cc.p(PROGRESS_BAR_SIZE.width * fromValue * 0.01, 0.5 * PROGRESS_BAR_SIZE.height), //右上
                cc.p(0, 0.5 * PROGRESS_BAR_SIZE.height)];                        //左上
            stencil.drawPoly(rect, cc.color(255, 255, 255, 255), 1, cc.color(255, 255, 255, 255));
            clipper.setStencil(stencil);
            this.addChild(clipper);

            var fromWidth = fromValue * 0.01 * PROGRESS_BAR_SIZE.width;
            var toWidth = toValue * 0.01 * PROGRESS_BAR_SIZE.width;
            var perFrame = (toWidth - fromWidth) / (duration * 60);//一帧60秒?

            var progress = new ccui.ImageView();
            progress.loadTexture("res/img_progress_bright.png");
            progress.ignoreContentAdaptWithSize(false);
            progress.setAnchorPoint(0, 0.5);
            progress.setContentSize(PROGRESS_BAR_SIZE);
            clipper.addChild(progress);
            clipper.scheduleUpdate();
            clipper.update = function () {
                fromWidth += perFrame;
                var rect = [cc.p(0, -0.5 * PROGRESS_BAR_SIZE.height),       //左下
                    cc.p(fromWidth, -0.5 * PROGRESS_BAR_SIZE.height),       //右下
                    cc.p(fromWidth, 0.5 * PROGRESS_BAR_SIZE.height),        //右上
                    cc.p(0, 0.5 * PROGRESS_BAR_SIZE.height)];               //左上
                var white = cc.color(255, 255, 255, 255);
                stencil.drawPoly(rect, white, 1, white);
                if (fromWidth >= toWidth) {
                    clipper.unscheduleUpdate();
                }
            }.bind(fromWidth);

        }.bind(this));


        return true;
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter: function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

