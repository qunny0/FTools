var BattleUtils = require('../common/BattleUtils');

var BattleData = require('./BattleData');

cc.Class({

    properties: {
        // _arrCardData: null,

        _arrCard: null,

        _arrCardOriginalPoint: null,

        _score: 0,

        _redCount: 0,

        _stepCount: 0,

        _battle: null,

        _battleConfig: null,

        _redCardMaxLevel: 2,
    },

    ctor: function (pbattle) {

        this._arrCard = [];

        this._arrCardOriginalPoint = [];

        this._score = 0;

        this._redCount = 0;

        this._stepCount = 0;

        this._battle = pbattle;

        this._redCardMaxLevel = 2,

        this._battleConfig = new BattleData(1);
    },

    getConfig: function() {
        return this._battleConfig;
    },

    pushcard: function(index, obj) {
        this._arrCard[index] = obj;

        this._arrCardOriginalPoint[index] = new cc.Vec2(obj.x, obj.y);

        // console.log('in', index, this._arrCardOriginalPoint[index]);
    },

    getCardByIndex: function(index) {
        return this._arrCard[index];
    },

    getCardImage: function(cardType, level) {
        let imgs = null;
        if (cardType == BattleUtils.CARD_TYPE.RED) {
            imgs = this._battleConfig._redCardShowCfg['level' + level];
        }
        else if (cardType == BattleUtils.CARD_TYPE.YELLOW) {
            imgs = this._battleConfig._yellowCardShowCfg['level' + level];
        }
        else if (cardType == BattleUtils.CARD_TYPE.BLUE) {
            imgs = this._battleConfig._blueCardShowCfg['level' + level];
        }

        if (!imgs || imgs.length == 0) {
            return null;
        }

        let img = imgs[0];
        if (imgs.length > 1) {
            let ran = Math.floor(Math.random() * imgs.length);
            img = imgs[ran];
        }

        return "res/CardImg/" + img;
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

    getRandomCardType: function () {
        let ran = Math.floor(Math.random() * 101);

        if (ran <= 40) {
            return [BattleUtils.CARD_TYPE.YELLOW, 1];
        }

        if (ran <= 76) {
            return [BattleUtils.CARD_TYPE.BLUE, 1];
        }

        if (this._redCardMaxLevel < 10) {
            if (this._stepCount > this._battleConfig._redCardLevelsByStep[this._redCardMaxLevel]) {
                this._redCardMaxLevel += 1;
            }
        }

        let redLevel = this._redCardMaxLevel;
        if (ran > 95) {
            redLevel = this._redCardMaxLevel - 1;
        }

        return [BattleUtils.CARD_TYPE.RED, redLevel];
    },

    generateCard (idx, dir) {
        this._stepCount += 1;

        this._battle.generateCard(idx, dir);
    },

    /**
     * 游戏是否结束
     */
    checkGameOver () {
        if (checkGameOver_CantMove()) {
            return true;
        }

        return false;
    },

    /**
     * 游戏是否结束。无法移动
     */
    checkGameOver_CantMove() {
        let len = this._arrCard.length;

        for (let i = 0; i < len; ++i) {
            let idx = this._arrCard[i].getComponent('Card').getIndex();

            let res = this.checkMove(idx, BattleUtils.CARD_MOVE_DIR.TOP);

            if (BattleUtils.checkMoveValid(res)) {
                return false;
            }

            res = this.checkMove(idx, BattleUtils.CARD_MOVE_DIR.RIGHT);

            if (BattleUtils.checkMove(res)) {
                return false;
            }
        }

        return true;
    },

});