
exports.X = 5;

exports.Y = 5;

exports.MOVE_RES = {
    'INVALID': -2,
    'OVERSTEP': -1,
    'YELLOW_COMBINE': 1,
    'BLUE_COMBINE': 2,
    'BLUE_YELLOW': 3,
    'BLUE_RED': 4,
}

exports.CARD_TYPE = {
    'BLUE': 0,
    'YELLOW': 1,
    'RED': 2,
};

exports.CARD_MOVE_DIR = {
    'STAND': 0,
    'TOP': 1,
    'BOTTOM': 2,
    'LEFT': 3,
    'RIGHT': 4,
    'INVALID': 5,
},

exports.CARD_Z_ORDER = {
    'DEFAULT': 0,
    'MOVE': 1,
},

exports.CARD_COLOR = [
    new cc.Color(81, 151, 213, 255),
    new cc.Color(233, 198, 68, 255),
    new cc.Color(178, 68, 53, 255),
];

exports.getPointByIndex = function (idx) {
    var x = idx % 5;
    var y = Math.floor(idx / 5);
    return {'x':x, 'y':y};
};

exports.getIndexByPoint = function (pt) {
    var idx = pt.y * 5 + pt.x;

    return idx;
};

exports.getToIndexByDir = function (oidx, dir) {
    let topt = this.getPointByIndex(oidx); 

    if (dir == this.CARD_MOVE_DIR.TOP) {
        topt.y += 1;
    }
    else if (dir == this.CARD_MOVE_DIR.BOTTOM) {
        topt.y -= 1;
    }
    else if (dir == this.CARD_MOVE_DIR.LEFT) {
        topt.x -= 1;
    }
    else if (dir == this.CARD_MOVE_DIR.RIGHT) {
        topt.x += 1;
    }

    let toIndex = this.getIndexByPoint(topt);

    return toIndex;
};

exports.checkMoveValid = function (ret) {
    if (ret == this.MOVE_RES.YELLOW_COMBINE ||
        ret == this.MOVE_RES.BLUE_COMBINE ||
        ret == this.MOVE_RES.BLUE_YELLOW ||
        ret == this.MOVE_RES.BLUE_RED) {
            return true;
        }

    return false;
};
