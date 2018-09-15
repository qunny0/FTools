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

        _moveDir: 0,

        _moveRes: 0,

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
        this._moveRes = BattleUtils.MOVE_RES.INVALID;
    },

    onTouch(e) {
        let type = e.type;

        if (type == 'touchstart') {
            // this._touchStartPoint = conPoint;
        }
        else if (type == 'touchmove') {

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

                if (absOfx > 20 || absOfY > 20) {
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
                this.node.zIndex = BattleUtils.CARD_Z_ORDER.MOVE;
            }
        }
        else if (type == 'touchend' || type == 'touchcancel') {
            let action = false;
            if (type == 'touchend') {
                if (BattleUtils.checkMoveValid(this._moveDir)) {
                    this.actionMoveOne();
                    action = true;
                }
            }

            if (!action) {
                this.node.zIndex = BattleUtils.CARD_Z_ORDER.DEFAULT;
                this.node.x = this._originPoint.x;
                this.node.y = this._originPoint.y;

                this.node.zIndex = BattleUtils.CARD_Z_ORDER.STAND;
            }
        }
        else {
            this._moveDir = BattleUtils.CARD_MOVE_DIR.STAND;
        }
    },

    setMoveDir (dir) {
        var ret = this._battleManager.checkMove(this._index, dir);

        if (BattleUtils.checkMoveValid(ret)) {
            this._moveRes = ret;
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

        this.node.zIndex = BattleUtils.CARD_Z_ORDER.DEFAULT;
    },

    //
    acLevelUP() {
        console.log('acLevelUP', this._index, this._type);

        this._level += 1;
        this.lbLevel.string = this._level;
    },

    resetIndex (idx) {
        this._index = idx;
        this.lbIndex.string = this._index;
    },

    //
    acBeEated() {
        this.node.destroy();
    },

    // 
    acMoveOneGrid(dir) {

    },

    acMoveTo(idx, tgtPt) {
        this.resetIndex(idx);

        this.node.x = tgtPt.x;
        this.node.y = tgtPt.y;
    },

    //
    acMove (dir) {

    },

    setPoint (pt) {
        console.log('setPoint', this._originPoint, pt);

        this._originPoint.x = pt.x;
        this._originPoint.y = pt.y;

        let acMoveTo = new cc.moveTo(0.2, cc.v2(pt.x, pt.y));
        this.node.runAction(acMoveTo);
    },

    acDisappear () {
        this._battleManager.setCard(this._index, null);
        this.node.destroy();
    },

    getIndex () {
        return this._index;
    },

    getCardInfo () {
        return [this._type, this._level]
    },

    getOriginalPoint () {
        return this._originPoint;
    },

    actionMoveOne () {
        let opt = BattleUtils.getPointByIndex(this._index);

        let toIndex = BattleUtils.getToIndexByDir(this._index, this._moveDir);
        let toCard = this._battleManager.getCardByIndex(toIndex);

        // let tox = toCard.node.x;
        // let toy = toCard.node.y;

        let toCardScript = toCard.getComponent('Card');
        let toCardPoint = toCardScript.getOriginalPoint();

        if (this._moveRes == BattleUtils.MOVE_RES.BLUE_COMBINE) {
            // toCard.LEVELUP
            // this.moveTo and disappoint
            // console.log('BLUE_COMBINE', this._index, toIndex);
            toCardScript.acLevelUP();
            this.acDisappear();
        }

        if (this._moveRes == BattleUtils.MOVE_RES.YELLOW_COMBINE) {
            // toCard.LEVELUP
            // this.moveTo and disappoint
            toCardScript.acLevelUP();
            this.acDisappear();
        }

        if (this._moveRes == BattleUtils.MOVE_RES.BLUE_RED) {
            // toCard.acEated
            // this.moveTo

            let cardinfo = toCardScript.getCardInfo();
            this._battleManager.eatCard(cardinfo[0], cardinfo[1]);

            toCardScript.acDisappear();

            // this.acMoveTo(toIndex, toCardPoint);
            this._battleManager.moveCard(this._index, toIndex);
        }

        if (this._moveRes == BattleUtils.MOVE_RES.BLUE_YELLOW) {
            // toCard.acEated
            // this.moveTo
            let cardinfo = toCardScript.getCardInfo();
            this._battleManager.eatCard(cardinfo[0], cardinfo[1]);

            toCardScript.acDisappear();
            // this.acMoveTo(toIndex, toCardPoint);
            this._battleManager.moveCard(this._index, toIndex);
        }

        let topoint = opt;
        let generateIndex = 0;
        let generateDir = 0;
        if (this._moveDir == BattleUtils.CARD_MOVE_DIR.TOP) {
            for (var i = topoint.y - 1; i >= 0; i--) {
                // obj move up
                topoint.y = i;
                let readyIndex = BattleUtils.getIndexByPoint(topoint);
                topoint.y = i + 1;
                let toIndex = BattleUtils.getIndexByPoint(topoint)

                this._battleManager.moveCard(readyIndex, toIndex);

                console.log(readyIndex, toIndex);
            }
            // generate: opt.x 0
            topoint.y = 0;
            generateDir = BattleUtils.CARD_MOVE_DIR.TOP;
            generateIndex = BattleUtils.getIndexByPoint(topoint);
        }
        
        if (this._moveDir == BattleUtils.CARD_MOVE_DIR.BOTTOM) {
            for (var i = topoint.y + 1; i < BattleUtils.Y; ++i) {
                topoint.y = i;
                let readyIndex = BattleUtils.getIndexByPoint(topoint);
                topoint.y = i - 1;
                let toIndex = BattleUtils.getIndexByPoint(topoint)

                this._battleManager.moveCard(readyIndex, toIndex);
                console.log(readyIndex, toIndex);
            }

            // generate: opt.x BattleUtils.Y - 1
            topoint.y = BattleUtils.Y - 1;
            generateDir = BattleUtils.CARD_MOVE_DIR.BOTTOM;
            generateIndex = BattleUtils.getIndexByPoint(topoint);

        }

        if (this._moveDir == BattleUtils.CARD_MOVE_DIR.LEFT) {
            for (var i = topoint.x + 1; i < BattleUtils.X; ++i) {
                // obj move left
                topoint.x = i;
                let readyIndex = BattleUtils.getIndexByPoint(topoint);
                topoint.x = i - 1;
                let toIndex = BattleUtils.getIndexByPoint(topoint)

                this._battleManager.moveCard(readyIndex, toIndex);
                console.log(readyIndex, toIndex);
            }
            // generate: BattleUtils.X-1, opt.y

            topoint.x = BattleUtils.X - 1;
            generateDir = BattleUtils.CARD_MOVE_DIR.LEFT;
            generateIndex = BattleUtils.getIndexByPoint(topoint);
        }

        if (this._moveDir == BattleUtils.CARD_MOVE_DIR.RIGHT) {
            for (var i = topoint.x - 1; i >= 0; --i) {
                // obj move right
                topoint.x = i;
                let readyIndex = BattleUtils.getIndexByPoint(topoint);
                topoint.x = i + 1;
                let toIndex = BattleUtils.getIndexByPoint(topoint)

                this._battleManager.moveCard(readyIndex, toIndex);
                console.log(readyIndex, toIndex);
            }
            // generate: 0, opt.y

            topoint.x = 0;
            generateDir = BattleUtils.CARD_MOVE_DIR.RIGHT;
            generateIndex = BattleUtils.getIndexByPoint(topoint);

        }

        console.log('gen', generateIndex, generateDir);

        this._battleManager.generateCard(generateIndex, generateDir);
    },
});
