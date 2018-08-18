var BattleUtils = require('../common/BattleUtils');

cc.Class({
    extends: cc.Component,

    properties: {

        lbIndex: {
            default: null,
            type: cc.Label,
        },

        lbLevel: {
            default: null,
            type: cc.Label,
        },

        _index: 0,

        _type: 0,

        _level: 0,

        _touchStartPoint: null,

        _moveDir: 0,

        _battleManager: null,

    },

    // LIFE-CYCLE CALLBACKS:

    onLoad () {
        this.node.on(cc.Node.EventType.TOUCH_START, this.onTouch, this);
        this.node.on(cc.Node.EventType.TOUCH_MOVE, this.onTouch, this);
        this.node.on(cc.Node.EventType.TOUCH_END, this.onTouch, this);
        this.node.on(cc.Node.EventType.TOUCH_CANCEL, this.onTouch, this);

        this._moveDir = BattleUtils.CARD_MOVE_DIR.STAND;
    },

    onTouch(e) {
        let type = e.type;
        // console.log(type);

        let point = e.touch._point;

        let conPoint = this.node.convertToNodeSpace(point);
        if (type == 'touchstart') {
            this._touchStartPoint = conPoint;
        }
        else if (type == 'touchmove') {
            if (this._touchStartPoint) {
                let ofx = conPoint.x - this._touchStartPoint.x;
                let ofy = conPoint.y - this._touchStartPoint.y;

                console.log('this._moveDir', this._moveDir);

                if (this._moveDir == BattleUtils.CARD_MOVE_DIR.STAND) {
                    let absOfx = Math.abs(ofx);
                    let absOfY = Math.abs(ofy);

                    if (absOfx > 10 || absOfY > 10) {
                        if (absOfx > absOfY) {
                            if (ofx > 0) {
                                this.setMoveDir(BattleUtils.CARD_MOVE_DIR.RIGHT);
                            }
                            else {
                                this.setMoveDir(BattleUtils.CARD_MOVE_DIR.LEFT);
                            }
                        }
                        else {
                            if (ofy > 0) {
                                this.setMoveDir(BattleUtils.CARD_MOVE_DIR.TOP);
                            }
                            else {
                                this.setMoveDir(BattleUtils.CARD_MOVE_DIR.BOTTOM);
                            }
                        }
                    }
                }
                else {

                }

                console.log(ofx, ofy)
            }
        }
        else if (type == 'touchend') {

        }
        else {
            this._touchStartPoint = null;
            this._moveDir = BattleUtils.CARD_MOVE_DIR.STAND;
        }
    },

    setMoveDir (dir) {

        var ret = this._battleManager.checkMove(this._index, dir);

        console.log(ret)

        if (ret == 0) {

        }
        else if (ret == 1) {

        }
        else {
            
        }

        // if (checkDir(dir)) {

        // }
        // else {

        // }
    },

    start () {

    },

    setData(gcp, idx, tp, level) {

        this._index = idx;
        this._battleManager = gcp;
        this._type = tp;
        this._level = level;

        console.log(this._type, typeof(this._type));

        this.node.color = BattleUtils.CARD_COLOR[this._type];
        this.lbLevel.string = this._level;

        this.lbIndex.string = idx;

        console.log(this._battleManager);
    },

    // update (dt) {},
});
