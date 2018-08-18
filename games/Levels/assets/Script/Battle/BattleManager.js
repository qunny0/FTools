var BattleUtils = require('../common/BattleUtils');

cc.Class({

    properties: {
        state: "sprite",

        // _arrCardData: null,

        _arrCard: null,
    },

    ctor: function () {
        cc.log('ctor');    // true
        this._arrCard = [];
    },

    pushcard: function(index, obj) {
        this._arrCard[index] = obj;
    },

    // init: function () {

    //     let count = BattleUtils.X * BattleUtils.Y
    //     for (var i = 0; i < count; i++) {
    //         _arrCardData.push()
    //     }
    // }

    /**
     * -1：超过边界
     */
    checkMove: function(idx, dir) {
        let card = this._arrCard[idx];

        let cardPoint = BattleUtils.getPointByIndex(idx);
        // let toPoint = idx;
        if (dir == BattleUtils.CARD_MOVE_DIR.TOP) {
            if (cardPoint.y == BattleUtils.Y - 1) {
                return 1;
            }
            cardPoint.y += 1;
        }
        else if (dir == BattleUtils.CARD_MOVE_DIR.BOTTOM) {
            if (cardPoint.y == 0) {
                return 1;
            }            
            cardPoint.y -= 1;
        }
        else if (dir == BattleUtils.CARD_MOVE_DIR.LEFT) {
            if (cardPoint.x == 0) {
                return 1;
            }
            cardPoint.x -= 1;
        }
        else if (dir == BattleUtils.CARD_MOVE_DIR.RIGHT) {
            if (cardPoint.x == BattleUtils.X - 1) {
                return 1;
            }
            cardPoint.y += 1;
        }

        let toIndex = BattleUtils.getIndexByPoint(cardPoint);
        let toCard = this._arrCard[toIndex];

        return 0;
    }
});