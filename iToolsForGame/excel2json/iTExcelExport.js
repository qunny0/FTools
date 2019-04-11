/**
 * 
 * npm init -f
 * npm install xlsx
 */

var process = require('process');
var iT_excel_format2json = require('./iT_excel_format2json');
var HUtils = require('../HUtils');
var path = require('path');

var G_CURPATH = path.dirname(__filename);

var arguments = process.argv.splice(2);

console.log(arguments[0] + ' -> ' + arguments[1]);

var excelDir = path.normalize(G_CURPATH + arguments[0]);

var outdir = path.normalize(G_CURPATH + arguments[1]);

var formatLuaPath = path.normalize(G_CURPATH + '/formatLua.lua')

var excelParse = iT_excel_format2json.ExcelParse.createObj();

HUtils.travelDir(excelDir, (file) => {

    let extname = path.extname(file);
    if (extname != '.xlsx') {
        return ;
    }

    let filename = path.basename(file, extname);
    if (filename.charAt(0) == '~') {
        return;
    }

    let basedir = path.dirname(file);
    let relativeDir = path.relative(excelDir, basedir);
    let reoutdir = path.join(outdir, relativeDir);

    console.log('---------------' + filename + '---------------');

    let res = excelParse.readExcel(file, reoutdir);

    if (res == 0) {
        console.log(file + ' export success!');

        if (!relativeDir) {
            relativeDir = '.'
        }
    }
    else {
        console.log(file + ' export failed. err: ' + res);
    }
});

// excelParse.setDataBeginLine(4);

