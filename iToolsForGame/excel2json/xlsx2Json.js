
/*
    读取一个xlsx中的指定数据转换为json格式，保存到json文件中

    1. 安装node
    2. 安装xlsx：npm install xlsx （如果安装不成功，运行npm init -f，然后再运行该命令）
*/


var XLSX = require('xlsx');
var fs = require('fs');
var path = require('path');
var util = require('util');
var HUtils = require('../HUtils')

const G_CUR_PATH = path.dirname(__filename)
HUtils.HCD(G_CUR_PATH);

var g_exportCode = 0;
/*
    0: success
    1: key duplicated
 */

// var g_dictTW = {
// };

var g_dictCN = {
};

var g_dictTW = {
};

function handleXLSX(file) {
    const workbook = XLSX.readFile(file, {
        "type": "string",
        "raw": true,
    });
    const sheetNames = workbook.SheetNames;
    const sheet = workbook.Sheets[sheetNames[0]];

    var index = 1;
    var actualLines = 0;
    do {
        index++;
        var skey = 'A' + index;
        var cn_value = 'C' + index;

        var tw_value = 'D' + index;
        // var en_value = 'G' + index;
        
        // 连续两行为空 表示该excel结束
        if (!sheet['A' + index] && !sheet['A' + (index+1)] && !sheet['A' + (index+2)]) {
            break;
        }

        if (!sheet[skey]) {
            continue;
        }

        var vkey = sheet[skey].v;

        if (sheet[tw_value]) {
            if (g_dictTW[vkey]) {
                console.log(vkey + " tw duplicated in file " + file);
                g_exportCode = 1;
                break;
            }
            var vvalue = sheet[tw_value].v;
            g_dictTW[vkey] = vvalue;
        }

        if (sheet[cn_value]) {
            if (g_dictCN[vkey]) {
                console.log(vkey + " cn duplicated in file " + file);
                g_exportCode = 1;
                break;
            }
            
            var vvalue = sheet[cn_value].v;
            g_dictCN[vkey] = vvalue;
        }

        // if (sheet[en_value]) {
        //     if (g_dictEN[vkey]) {
        //         console.log(vkey + " cn duplicated in file " + file);
        //         g_exportCode = 1;
        //         break;
        //     }
            
        //     var vvalue = sheet[en_value].v;
        //     g_dictEN[vkey] = vvalue;
        // }

        actualLines++;
    } while (true)

    let filename = path.basename(file);

    if (g_exportCode == 0) {
        console.log('export ' + filename + '\tsuccess ^_^ ^_^' + ' : have ' + index + ' lines, actual export ' + actualLines + ' lines.');
    }
}

// local lua_dir_version = PATH.. '../../../config/version'

const g_fileList = [
    path.normalize(G_CUR_PATH + "/../../../config/language_excel/tipsCfg.xlsx"),
    path.normalize(G_CUR_PATH + "/../../../config/language_excel/storyCfg.xlsx"),
];

g_fileList.forEach(file => {

    var filepath = file;

    if (g_exportCode == 0) {
        var exist = fs.existsSync(filepath);
        if (exist) {
            handleXLSX(filepath);
        }
        else {
            console.log(file + " not exist！！！");
        }
    }
});

var fs = require('fs');

function real_write(dic, dicFile)
{
    console.log('write file -> ', dicFile);

    var outputFilename = dicFile;
    var outputDir = path.dirname(outputFilename);

    if (!fs.existsSync(outputDir)) {
        fs.mkdirSync(outputDir);
    }

    fs.writeFileSync(outputFilename, '{\n');
    var objKeys = Object.keys(dic);
    for (let index = 0; index < objKeys.length; index++) {
        var str = "";
        if (index == objKeys.length - 1) {
            str = util.format('  \"%s\":\"%s\"\n', objKeys[index], dic[objKeys[index]])
        }
        else {
            str = util.format('  \"%s\":\"%s\",\n', objKeys[index], dic[objKeys[index]]);
        }
        fs.writeFileSync(outputFilename, str, { flag: 'a' });
    }

    fs.writeFileSync(outputFilename, '}', { flag: 'a' });
}

if (g_exportCode == 0) {
    var twFilename = path.normalize(G_CUR_PATH + "/../../../config/language/tw.json");

    real_write(g_dictTW, twFilename);

    var cnFilename = path.normalize(G_CUR_PATH + "/../../../config/language/cn.json");

    real_write(g_dictCN, cnFilename);

    // var enFilename = G_CUR_PATH + '../../language/en.json';

    // real_write(g_dictEN, enFilename);
}
else {
    if (g_exportCode == 1) {
        console.log("export failed. Because KEY duplicated !!");
    }
}
