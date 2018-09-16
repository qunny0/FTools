var ConfigManager = require('./Manager/ConfigManager');

cc.Class({
    extends: cc.Component,

    properties: {
        battlePb: {
            default: null,
            type: cc.Prefab
        },

        _startBattle: false,
    },

    ctor () {

    },

    // use this for initialization
    onLoad: function () {

    },

    start: function () {

    },

    // called every frame
    update: function (dt) {
        if (!this._startBattle && ConfigManager.getInstance()._init) {
            this._startBattle = true;
            this.startBattle();
        }
    },

    startBattle: function() {
        let inst = cc.instantiate(this.battlePb);
        this.node.addChild(inst);
    }
});
