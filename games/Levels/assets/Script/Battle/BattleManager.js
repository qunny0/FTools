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
     * 1: yellow combine
     * 2: blue combine
     */
    checkMove: function(idx, dir) {

        let cardPoint = BattleUtils.getPointByIndex(idx);
        // let toPoint = idx;
        if (dir == BattleUtils.CARD_MOVE_DIR.TOP) {
            if (cardPoint.y == BattleUtils.Y - 1) {
                return BattleUtils.MOVE_RES.OVERSTEP;
            }
            cardPoint.y += 1;
        }
        else if (dir == BattleUtils.CARD_MOVE_DIR.BOTTOM) {
            if (cardPoint.y == 0) {
                return BattleUtils.MOVE_RES.OVERSTEP;
            }            
            cardPoint.y -= 1;
        }
        else if (dir == BattleUtils.CARD_MOVE_DIR.LEFT) {
            if (cardPoint.x == 0) {
                return BattleUtils.MOVE_RES.OVERSTEP;
            }
            cardPoint.x -= 1;
        }
        else if (dir == BattleUtils.CARD_MOVE_DIR.RIGHT) {
            if (cardPoint.x == BattleUtils.X - 1) {
                return BattleUtils.MOVE_RES.OVERSTEP;
            }
            cardPoint.x += 1;
        }

        let toIndex = BattleUtils.getIndexByPoint(cardPoint);
        
        let card = this._arrCard[idx];
        let toCard = this._arrCard[toIndex];

        let cardInfo = card.getComponent('Card').getCardInfo();
        let toCardInfo = toCard.getComponent('Card').getCardInfo();

        let ctype = cardInfo[0];
        let clevel = cardInfo[1];

        let ttype = toCardInfo[0];
        let tlevel = toCardInfo[1];

        // console.log(idx, toIndex, ctype, clevel, ttype, tlevel);

        if (ctype == BattleUtils.CARD_TYPE.YELLOW) {
            if (clevel == tlevel && ttype == BattleUtils.CARD_TYPE.YELLOW) {
                return BattleUtils.MOVE_RES.YELLOW_COMBINE;
            }
            return BattleUtils.MOVE_RES.INVALID;
        }

        if (ctype == BattleUtils.CARD_TYPE.BLUE) {
            if (ttype == BattleUtils.CARD_TYPE.BLUE && clevel == tlevel) {
                return BattleUtils.MOVE_RES.BLUE_COMBINE;
            }

            if (ttype == BattleUtils.CARD_TYPE.RED && clevel >= tlevel) {
                return BattleUtils.MOVE_RES.BLUE_RED;
            } 

            if (ttype == BattleUtils.CARD_TYPE.YELLOW && clevel >= tlevel) {
                return BattleUtils.MOVE_RES.BLUE_YELLOW;
            }

            return BattleUtils.MOVE_RES.INVALID;
        }

        return BattleUtils.MOVE_RES.INVALID;
    }
});