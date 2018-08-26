/**
 * 
 * npm init -f
 * npm install xlsx
 */

var process = require('process');
var iT_excel_format2json = require('./iT_excel_format2json');
var iTJSUtils = require('../jsCommon/iTJSUtils');
var path = require('path');

var arguments = process.argv.splice(2);

var excelDir = arguments[0];

var outdir = arguments[1];

var excelParse = iT_excel_format2json.ExcelParse.createObj();

iTJSUtils.travelDir(excelDir, (file) => {

    let extname = path.extname(file);
    if (extname != '.xlsx') {
        return ;
    }

    let filename = path.basename(file, extname);
    if (filename.charAt(0) == '~') {
        return;
    }

    console.log('---------------' + filename + '---------------');

    let res = excelParse.export2(file, outdir);

    if (res == 0) {
        console.log(file + ' export success!');
    }
    else {
        console.log(file + ' export failed. err: ' + res);
    }
});

// excelParse.setDataBeginLine(4);

