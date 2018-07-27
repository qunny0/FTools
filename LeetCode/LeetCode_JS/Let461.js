/**
 * @param {number} x
 * @param {number} y
 * @return {number}
 */
var hammingDistance = function (x, y) {
    var num = 0;

    while( x != 0 || y != 0) {
        var xbit = x % 2;
        var ybit = y % 2;

        console.log(xbit, ybit);

        if (xbit != ybit) {
            num = num + 1;
        }

        x = Math.floor(x / 2);
        y = Math.floor(y / 2);
    }

    return num;
};

var res = hammingDistance(65536, 4);

console.log(res);