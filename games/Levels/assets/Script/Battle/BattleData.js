/**
 * 关卡配置数据
 * 数据初始化完毕后，游戏过程中不会进行修改
 */

var ConfigManager = require('../Manager/ConfigManager');

var BattleUtils = require('../common/BattleUtils');

cc.Class({

    properties: {

        // 关卡初始化卡牌数目 {type, level}
        _initCard: [],

        // 本关卡是否出现黄牌
        _haveYellowCard: true,

        // 本关卡是否出现红牌
        _havaRedCard: true,

        // 红卡：出现等级的步骤限制
        _redCardLevelsByStep: [],

        _blueCardShowCfg: [],

        _yellowCardShowCfg: [],

        _redCardShowCfg: [],
    },

    ctor: function(challengeID) {
        console.log('BattleData.init', challengeID);
        let self = this;

        let challengeCfg = ConfigManager.getInstance().Challenge[String(challengeID)];

        console.log(challengeCfg);

        function insertTypeCard(tp, cardStrs) {
            let cardStrArr = cardStrs.split(';');

            cardStrArr.forEach(ele => {
                let cardArr = ele.split('|');

                for (let i = 0; i < cardArr[0]; i++) {
                    self._initCard.push([tp, Number(cardArr[1])]);
                }
            });
        }

        insertTypeCard(BattleUtils.CARD_TYPE.BLUE, challengeCfg.initBlueCard);
        insertTypeCard(BattleUtils.CARD_TYPE.YELLOW, challengeCfg.initYellowCard);
        insertTypeCard(BattleUtils.CARD_TYPE.RED, challengeCfg.initRedCard);

        let rhalf = Math.floor(this._initCard.length / 2);
        for (var i = 0; i < rhalf; i++) {
            let r = Math.floor(Math.random() * rhalf);
            let e = r + rhalf;

            [this._initCard[r], this._initCard[e]] = [this._initCard[e], this._initCard[r]];
        }

    },

    getInitCard: function() {
        return this._initCard;
    },


})