var BattleUtils = require('../common/BattleUtils');

cc.Class({
    extends: cc.Component,

    properties: {

        _type: 0,

        _level: 0,

    },

    // LIFE-CYCLE CALLBACKS:

    // onLoad () {},

    start () {

    },

    setData(tp, level) {

        this._type = tp;
        this._level = level;

        console.log(this._type, typeof(this._type));

        this.node.color = BattleUtils.CARD_COLOR[this._type];
    },

    // update (dt) {},
});
