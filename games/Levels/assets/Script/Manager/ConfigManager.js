const CONFIG_LIST = [
    'Dict',
    'GameConfig',
    'Trigger'
]

var ConfigManager =  cc.Class({
    statics: {
        _instance: null,
    },

    properties: {

        _init: false,

        Dict: null,
        GameConfig: null,
        Trigger: null,

        configList:{
            type: Array,
            default: [],
        }
    },

    
    start () {

    },

    loadConfig (cb) {
        let self = this;

        console.log('this', this);

        let totalLen = CONFIG_LIST.length;

        let loadidx = 0;
        CONFIG_LIST.forEach(cfg => {
            let cfgpath = 'config/' + cfg;

            cc.loader.loadRes(cfgpath, function (err, jsonAsset) {
                self[cfg] = jsonAsset.json;

                if (++loadidx == totalLen) {
                    self._init = true;
                }

                cb(loadidx, totalLen);
            });
        });
    },

    init () {
        console.log("ConfigManager init");
    }
});


ConfigManager.getInstance = function () {
    if (!this._instance) {
        this._instance = new ConfigManager();
    }

    return ConfigManager._instance;
}

module.exports = ConfigManager;