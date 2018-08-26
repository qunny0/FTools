/**
 * 
 * 一些通用方法
 */

var fs = require("fs");

function travelDir(dir, callback) {
    var pa = fs.readdirSync(dir);
    pa.forEach(function (ele, index) {
        var pdir = dir + '/' + ele;
        var info = fs.statSync(pdir);
        if (info.isDirectory()) {
            travelDir(pdir, callback);
        }
        else if (info.isFile()) {
            callback(pdir);
        }
    })
}

exports.travelDir = travelDir;