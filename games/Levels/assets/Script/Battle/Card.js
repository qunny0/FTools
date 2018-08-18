var BattleUtils = require('../common/BattleUtils');

cc.Class({
    extends: cc.Component,

    properties: {

        // _type = 0,
    
    },

    // LIFE-CYCLE CALLBACKS:

    // onLoad () {},

    start () {

    },

    setData(type, level) {
        this.node.color = BattleUtils.CARD_BLUE;
    },

    // update (dt) {},
});
