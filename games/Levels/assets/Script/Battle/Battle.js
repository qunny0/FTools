var BattleUtils = require('../common/BattleUtils');
var BattleManager = require('../Battle/BattleManager');

cc.Class({
    extends: cc.Component,

    properties: {
        // foo: {
        //     // ATTRIBUTES:
        //     default: null,        // The default value will be used only when the component attaching
        //                           // to a node for the first time
        //     type: cc.SpriteFrame, // optional, default is typeof default
        //     serializable: true,   // optional, default is true
        // },
        // bar: {
        //     get () {
        //         return this._bar;
        //     },
        //     set (value) {
        //         this._bar = value;
        //     }
        // },

        lbStep: {
            default: null,
            type: cc.Label
        },

        lbScore: {
            default: null,
            type: cc.Label
        },

        lbRed: {
            default: null,
            type: cc.Label
        },

        lbBest: {
            default: null,
            type: cc.Label
        },

        cardPanel: {
            default: null,
            type: cc.Node
        },

        cardPb: {
            default: null,
            type: cc.Prefab
        },

        _battleManager: null,
    },

    start () {
        this.lbScore.string = '';
        this.lbBest.string = '';
        
        this._battleManager = new BattleManager(this);

        this.initGame();
    },

    initGame () {
        let count = BattleUtils.X * BattleUtils.Y

        var initArr = [];

        var yellowCount = 0;
        var blueCount = 0;
        var redCount = 0;

        for (var i = 0; i < count; i++) {
            if (yellowCount < 10) {
                yellowCount += 1;
                initArr.push([BattleUtils.CARD_TYPE.YELLOW, 1]);
            }
            else if (blueCount < 9) {
                blueCount += 1;
                initArr.push([BattleUtils.CARD_TYPE.BLUE, 1]);
            }
            else {
                redCount += 1;
                if (redCount <= 4) {
                    initArr.push([BattleUtils.CARD_TYPE.RED, 1]);
                }
                else {
                    initArr.push([BattleUtils.CARD_TYPE.RED, 2]);
                }
            }
        }

        let rhalf = Math.floor(count/2);
        for (var i = 0; i < rhalf; i++) {
            let r = Math.floor(Math.random() * rhalf);
            let e = r + rhalf;

            [initArr[r], initArr[e]] = [initArr[e], initArr[r]];
        }

        for (var i = 0; i < count; i++) {
            var pt = BattleUtils.getPointByIndex(i);

            var obj = cc.instantiate(this.cardPb);

            obj.x = pt.x * 140;
            obj.y = pt.y * 190;

            obj.getComponent('Card').setData(this._battleManager, i, initArr[i][0], initArr[i][1]);

            this.cardPanel.addChild(obj);

            this._battleManager.pushcard(i, obj);
        }
    },

    generateCard(idx, dir) {
        this.refreshScore();

        var ct = BattleUtils.getRandomCardType();

        var obj = cc.instantiate(this.cardPb);

        let op = this._battleManager.getPointByIndex(idx);

        obj.x = op.x;
        obj.y = op.y;

        obj.getComponent('Card').setData(this._battleManager, idx, ct, 1);

        let originPt = new cc.v2(op.x, op.y);
        if (dir == BattleUtils.CARD_MOVE_DIR.TOP) {
            originPt.y -= 230;
        }
        else if (dir == BattleUtils.CARD_MOVE_DIR.BOTTOM) {
            originPt.y += 230;
        }
        else if (dir == BattleUtils.CARD_MOVE_DIR.LEFT) {
            originPt.x += 180;
        }
        else if (dir == BattleUtils.CARD_MOVE_DIR.RIGHT) {
            originPt.x -= 180;
        }

        obj.x = originPt.x;
        obj.y = originPt.y;

        // console.log('generate', idx, dir, obj.x, obj.y);

        obj.getComponent('Card').setPoint(op);

        this.cardPanel.addChild(obj);

        this._battleManager.setCard(idx, obj);
    },

    refreshScore() {
        this.lbScore.string = this._battleManager.getScore();

        this.lbRed.string = this._battleManager.getRed();

        this.lbStep.string = this._battleManager.getStep();
    }

    // update (dt) {},
});
