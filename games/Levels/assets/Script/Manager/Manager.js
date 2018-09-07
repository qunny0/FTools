var ConfigManager = require('./ConfigManager');

cc.Class({
    extends: cc.Component,

    onLoad () {
        cc.game.addPersistRootNode(this.node);

        this.initGlobal();
    },

    initGlobal() {
        G.configManager = ConfigManager.getInstance();
        G.configManager.loadConfig((loadidx, totallen) => {
            console.log('--', loadidx, totallen);
        })
    }
});
