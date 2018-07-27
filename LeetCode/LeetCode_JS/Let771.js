/**
 * @param {string} J
 * @param {string} S
 * @return {number}
 */
var numJewelsInStones = function(J, S) {
    var num = 0;

    var array_s = {};
    for (var chr of S) {
        if (!array_s[chr]) {
            array_s[chr] = 1;
        }
        else {
            array_s[chr] += 1;
        }
    }

    for (var chr of J) {
        if (array_s[chr]) {
            num += array_s[chr];
        }
    }

    return num;
};


numJewelsInStones('aA', 'aAAbbbbaAAbbbbaAAbbbbaAAbbbbaAAbbbbaAAbbbbaAAbbbbaAAbbbbaAAbbbbaAAbbbb');

