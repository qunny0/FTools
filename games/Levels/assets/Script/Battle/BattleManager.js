var BattleUtils = require('../common/BattleUtils');

cc.Class({

    properties: {
        state: "sprite",

        _arrCardData: null,
    },

    ctor: function () {
        cc.log('ctor');    // true
    },

    init: function () {

        let count = BattleUtils.X * BattleUtils.Y
        for (var i = 0; i < count; i++) {
            _arrCardData.push()
        }
    }
});