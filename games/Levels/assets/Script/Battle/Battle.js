var BattleUtils = require('../common/BattleUtils');

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

        lbScore: {
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

        // _arrCard: {
        //     get () {
        //         return _arrCard;
        //     },
        //     set (val) {
        //         this._arrCard = val;
        //     }
        // },
    },

    // LIFE-CYCLE CALLBACKS:

    // onLoad () {},

    start () {
        this.lbScore.string = '';
        this.lbBest.string = '';
        
        this.initGame();
    },

    initGame () {
        let count = BattleUtils.X * BattleUtils.Y
        for (var i = 0; i < count; i++) {
            var pt = BattleUtils.getPointByIndex(i);

            console.log(i, pt);

            var obj = cc.instantiate(this.cardPb);

            obj.x = pt.x * 140;
            obj.y = pt.y * 190;

            obj.getComponent('Card').setData(1,1);

            this.cardPanel.addChild(obj);
        }

        // for (var i = 0; i < )

        // var pt = BattleUtils.getPointByIndex(1);
        // console.log(pt);
    }

    // update (dt) {},
});
