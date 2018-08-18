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

        _originPoint: null,
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

        // let conPoint = e.touch.getStartLocation();

        if (type == 'touchstart') {
            // this._touchStartPoint = conPoint;
        }
        else if (type == 'touchmove') {

            // console.log('this._moveDir', this._moveDir);


            if (this._moveDir == BattleUtils.CARD_MOVE_DIR.INVALID) {
                return ;
            }

            if (this._moveDir == BattleUtils.CARD_MOVE_DIR.STAND) {
                let startPoint = e.touch.getStartLocation();
                let conPoint = e.touch.getLocation();

                let ofx = conPoint.x - startPoint.x;
                let ofy = conPoint.y - startPoint.y;

                let absOfx = Math.abs(ofx);
                let absOfY = Math.abs(ofy);

                // console.log('', absOfx, absOfY);

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
                let startPoint = e.touch.getStartLocation();
                let conPoint = e.touch.getLocation();

                let offPoint = new cc.Vec2(0, 0);
                if (this._moveDir == BattleUtils.CARD_MOVE_DIR.TOP) {
                    let offy = conPoint.y - startPoint.y;
                    if (offy > 0 && offy < 180) {
                        offPoint.y += offy;
                    }
                }
                else if (this._moveDir == BattleUtils.CARD_MOVE_DIR.BOTTOM) {
                    let offy = conPoint.y - startPoint.y;
                    if (offy < 0 && offy > -180) {
                        offPoint.y += offy;
                    }
                }
                else if (this._moveDir == BattleUtils.CARD_MOVE_DIR.LEFT) {
                    let offx = conPoint.x - startPoint.x
                    if (offx < 0 && offx > -150) {
                        offPoint.x += offx;
                    }
                }
                else if (this._moveDir == BattleUtils.CARD_MOVE_DIR.RIGHT) {
                    let offx = conPoint.x - startPoint.x
                    if (offx > 0 && offx < 150) {
                        offPoint.x += offx;
                    }
                }

                this.node.x = this._originPoint.x + offPoint.x;
                this.node.y = this._originPoint.y + offPoint.y;
            }
        }
        else if (type == 'touchend' || type == 'touchcancel') {
            this._moveDir = BattleUtils.CARD_MOVE_DIR.STAND;
            this.node.x = this._originPoint.x;
            this.node.y = this._originPoint.y;
        }
        else {
            this._moveDir = BattleUtils.CARD_MOVE_DIR.STAND;
        }
    },

    setMoveDir (dir) {

        var ret = this._battleManager.checkMove(this._index, dir);

        // console.log('setMoveDir', ret, dir)

        if (ret == 1) {
            this._moveDir = BattleUtils.CARD_MOVE_DIR.INVALID;
            return ;
        }

        if (ret == BattleUtils.MOVE_RES.BLUE_COMBINE ||
            ret == BattleUtils.MOVE_RES.YELLOW_COMBINE ||
            ret == BattleUtils.MOVE_RES.BLUE_RED ||
            ret == BattleUtils.MOVE_RES.BLUE_YELLOW) {
            this._moveDir = dir;
            return ;
        }
    },

    start () {

    },

    setData(gcp, idx, tp, level) {

        this._index = idx;
        this._battleManager = gcp;
        this._type = tp;
        this._level = level;

        this.node.color = BattleUtils.CARD_COLOR[this._type];
        this.lbLevel.string = this._level;

        this.lbIndex.string = idx;

        this._originPoint = new cc.Vec2(this.node.x, this.node.y);
    },

    getType () {
        return this._type;
    },

    getIndex () {
        return this._index;
    },

    getLevel () {
        return this._level;
    },

    getCardInfo () {
        return [this._type, this._level]
    }
});
