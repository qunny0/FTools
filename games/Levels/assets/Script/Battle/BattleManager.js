var BattleUtils = require('../common/BattleUtils');

cc.Class({

    properties: {
        // state: "sprite",

        // _arrCardData: null,

        _arrCard: null,

        _arrCardOriginalPoint: null,

        _score: 0,

        _redCount: 0,

        _stepCount: 0,

        _battle: null,
    },

    ctor: function (pbattle) {

        this._arrCard = [];

        this._arrCardOriginalPoint = [];

        this._score = 0;

        this._redCount = 0;

        this._stepCount = 0;

        this._battle = pbattle;
    },

    pushcard: function(index, obj) {
        this._arrCard[index] = obj;

        this._arrCardOriginalPoint[index] = new cc.Vec2(obj.x, obj.y);

        console.log('in', index, this._arrCardOriginalPoint[index]);

    },

    getCardByIndex: function(index) {
        return this._arrCard[index];
    },

    getScore: function () {
        return this._score;
    },

    getRed: function () {
        return this._redCount;
    },

    getStep: function () {
        return this._stepCount;
    },

    /**
     * BattleUtils.MOVE_RES
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

        // console.log(ctype == BattleUtils.CARD_TYPE.YELLOW, clevel == tlevel, ttype == BattleUtils.CARD_TYPE.YELLOW);
        
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
    },

    actionMove: function (idx, dir, moveres) {

    },

    moveCard (oidx, tidx) {
        let obj = this._arrCard[oidx];

        obj.getComponent('Card').setPoint(this._arrCardOriginalPoint[tidx]);

        obj.getComponent('Card').resetIndex(tidx);
        
        this._arrCard[tidx] = this._arrCard[oidx];
    },

    setCard (idx, card) {
        this._arrCard[idx] = card;
    },

    getPointByIndex (idx) {
        return this._arrCardOriginalPoint[idx];
    },

    eatCard (ctype, clevel) {
        console.log('eatCard', ctype, clevel);
        if (ctype == BattleUtils.CARD_TYPE.YELLOW) {
            this._score += clevel;
        }
        else if (ctype == BattleUtils.CARD_TYPE.RED) {
            this._redCount += clevel;
        }
    },

    generateCard (idx, dir) {
        this._stepCount += 1;

        this._battle.generateCard(idx, dir);
    },

});