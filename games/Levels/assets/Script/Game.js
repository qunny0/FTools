cc.Class({
    extends: cc.Component,

    properties: {
        battlePb: {
            default: null,
            type: cc.Prefab
        }
        
    },

    // use this for initialization
    onLoad: function () {
    },

    start: function () {
        let inst = cc.instantiate(this.battlePb);
        this.node.addChild(inst);
    },

    // called every frame
    update: function (dt) {

    },

});
