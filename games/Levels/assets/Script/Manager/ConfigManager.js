const CONFIG_LIST = [
    'Dict',
    'GameConfig',
    'Trigger',
    'HeroDisplay',
    'Challenge',
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
        HeroDisplay: null,
        Challenge: null,

        configList:{
            type: Array,
            default: [],
        }
    },

    
    start () {

    },

    loadConfig (cb) {
        let self = this;

        let totalLen = CONFIG_LIST.length;

        let loadidx = 0;
        CONFIG_LIST.forEach(cfg => {
            let cfgpath = 'config/' + cfg;

            cc.loader.loadRes(cfgpath, function (err, jsonAsset) {
                if (!err) {
                    self[jsonAsset._name] = jsonAsset.json;

                    if (++loadidx == totalLen) {
                        self._init = true;
                    }

                    console.log('load config ' + jsonAsset._name + ' success!');

                    cb(loadidx, totalLen);
                }
                else {
                    console.log('load config ' + jsonAsset._name + ' failed!');
                }
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