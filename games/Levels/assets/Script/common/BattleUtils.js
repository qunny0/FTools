
exports.X = 5;

exports.Y = 5;

exports.CARD_TYPE = {
    'BULE': 0,
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

exports.CARD_COLOR = [
    new cc.Color(81, 151, 213, 255),
    new cc.Color(233, 198, 68, 255),
    new cc.Color(178, 68, 53, 255),
];

// exports.CARD_BLUE = new cc.Color(81, 151, 213, 255);

// exports.CARD_YELLOW = new cc.Color(233, 198, 68, 255);

// exports.CARD_RED = new cc.Color(178, 68, 53, 255);

exports.getPointByIndex = function (idx) {
    var x = idx % 5;
    var y = Math.floor(idx / 5);
    return {'x':x, 'y':y};
};

exports.getIndexByPoint = function (pt) {
    return 1;
};

