var fs = require("fs");

/**
 * @param {number} x
 * @param {number} y
 * @return {number}
 */
var hammingDistance = function (x, y) {
    var num = 0;

    while (x != 0 || y != 0) {
        var xbit = x % 2;
        var ybit = y % 2;

        if (xbit != ybit) {
            num = num + 1;
        }

        x = Math.floor(x / 2);
        y = Math.floor(y / 2);
    }

    return num;
};

/**
 * @param {number[]} nums
 * @return {number}
 */
var totalHammingDistance = function (nums) {
    // var num = 0;
    // for (i = 0; i < nums.length; ++i) {
    //     for (j = i + 1; j < nums.length; ++j) {
    //         num += hammingDistance(nums[i], nums[j]);
    //     }
    // }

    // return num;

    var num = 0;

    for (i = 0; i < 32; ++i) {
        var digit = 0;
        for (j = 0; j < nums.length; ++j) {
            digit += (nums[j] >> i) & 1;
        }
        num += digit * (nums.length - digit);
    }

    return num;
};

function generateTestCase() {
    // Elements of the given array are in the range of 0 to 10 ^ 9
    // Length of the array will not exceed 10 ^ 4.
    // var test = [];
    // for (i = 0; i < 10000; ++i) {
    //     var rNum = Math.floor(Math.random()*1000000000);
    //     test.push(rNum);
    // }

    var assetsMd5File = '/Users/ben/Desktop/leetTest.json';
    // fs.writeFileSync(assetsMd5File, JSON.stringify(test));

    var testcase = JSON.parse(fs.readFileSync(assetsMd5File));

    // var assetsCfgFile = G_CURPATH + '/../../art_pub/resources/assets_res_type_config.json';
    // if (fs.existsSync(assetsCfgFile)) {
    //     var data = fs.readFileSync(assetsCfgFile);
    //     assetsCfg = JSON.parse(data);

    return testcase;
}

// generateTestCase();


var res = totalHammingDistance(generateTestCase());

console.log(res);