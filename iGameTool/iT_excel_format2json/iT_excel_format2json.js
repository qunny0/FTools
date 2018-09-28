/*
    读取一个xlsx中的指定数据转换为json格式，保存到json文件中

    1. 安装node
    2. 安装xlsx：npm install xlsx （如果安装不成功，运行npm init -f，然后再运行该命令）
*/


var XLSX = require('xlsx');
var fs = require('fs');
var path = require('path');
// var json2lua = require('json2lua');

var iJson2Lua = require('./iJson2Lua');

var RES_SUCCESS = 0;
var RES_EXCEL_ERR = 100;
var RES_EXCEL_NOTFOUND = 101;
var RES_DATA_FORMAT_ERR = 300;
var RES_DATA_PARSE_ERR = 301;
var RES_WRITE_ERR = 400;

let ExcelParse = {

    supportType: [
        'string',
        'boolean',
        'number',
        'array',
        'link',
    ],

    createObj: function (){

        var excelParse = {};

        // 数据key所在行
        var _data_key_line = XLSX.utils.decode_row('1');

        // 数据类型所在行
        var _data_type_line = XLSX.utils.decode_row('3');

        // 数据开始行
        var _data_begin_line = XLSX.utils.decode_row('4');

        // data_keys
        var _arrKeys = [];

        // data_types
        var _arrTypes = [];

        var _worksheet = null;

        var _columns = 0;

        var _tableName = null;

        var _resErr = RES_SUCCESS;

        reset = function () {
            _arrKeys = [];
            _arrTypes = [];

            _columns = 0;

            _resErr = RES_SUCCESS;
        }

        typeSupport = function (v) {
            let idx = ExcelParse.supportType.indexOf(v);

            if (idx != -1) {
                return idx;
            }

            if (v.substring(0, 5) == 'link_') {
                return 0;
            }

            return -1;
        }

        getValue = function (v, idx) {
            if (_arrTypes[idx] == ExcelParse.supportType[0]) {
                return v;
            }

            if (_arrTypes[idx] == ExcelParse.supportType[1]) {
                return Number(v) == 1;
            }

            if (_arrTypes[idx] == ExcelParse.supportType[2]) {
                return Number(v);
            }

            if (_arrTypes[idx] == ExcelParse.supportType[3]) {
                return v.split(',');
            }

            if (_arrTypes[idx].substring(0, 5) == 'link_') {
                if (Number(v)) {
                    return _arrTypes[idx] + '_' + String(v);
                }
                else {
                    let arr = v.split(',');

                    let arrdata = {};

                    for (let i = 0; i < arr.length; ++i) {
                        if (arr[i]) {
                            // arr[i] = _arrTypes[idx] + '_' + arr[i];

                            arrdata[arr[i]] = _arrTypes[idx] + '_' + arr[i];
                        }
                        else {  // 最后逗号的情况
                            arr.splice(i, 1);
                        }
                    }

                    return arrdata;
                }
            }

            throw new Error(idx + ' - ' + v);
        }

        isComment = function (idx) {
            // console.log('==', _arrKeys, idx);
            return _arrKeys[idx].indexOf('#') == 0
        }

        writeFile = function (outdir, cfgdata) {

            var outfile = path.normalize(outdir + '/' + _tableName + '.json');

            var outputDir = path.dirname(outfile);

            if (!fs.existsSync(outputDir)) {
                fs.mkdirSync(outputDir);
            }

            let jsondata = JSON.stringify(cfgdata);

            console.log(jsondata);            

            fs.writeFileSync(outfile, jsondata);
        }

        writeFileAsLua = function (outdir, cfgdata) {

            var outfile = path.normalize(outdir + '/' + _tableName + '.lua');

            var outputDir = path.dirname(outfile);

            if (!fs.existsSync(outputDir)) {
                fs.mkdirSync(outputDir);
            }

            let jsondata = JSON.stringify(cfgdata);

            let luaTable = iJson2Lua.fromString(jsondata);

            let luastring = 'local ' + _tableName + ' = ' + luaTable + ' \nreturn ' + _tableName;

            fs.writeFileSync(outfile, luastring);
        }

        /**
         * [false|true, rewardtype|rewardid|rewardnum, ''|'1'|'2']
         * return: [match, matchstr, index]
         */
        checkRewardReg = function (keysValue) {
            let rewardReg = /reward(type|id|num)/

            let res = rewardReg.exec(keysValue);

            if (!res || res.index != 0) {
                return [false];
            }

            // console.log(res[0]);

            let remainstr = keysValue.substr(res[0].length);

            let idxstr = remainstr;

            if (idxstr.length > 0) {
                let remainnum = Number(remainstr);

                if (!remainnum) {
                    // console.log('======191===!remainnum')
                    return [false];
                }
            }

            // console.log('===195==', res[0], idxstr);

            return [true, res[0], idxstr]
        }

        excelParse.setDataBeginLine = function (v) {
            _data_begin_line = XLSX.utils.decode_row('' + v);
        }

        excelParse.getDataBeginLine = function () {
            return _data_begin_line;
        }

        excelParse.mergeSheet = function (arrSheet, defaultSheet) {
            console.log('merge');
            
            let mergedFlag = {};

            getLinkData = function (sheetname, id) {
                if (!mergedFlag[sheetname]) {
                    merge_once(sheetname);
                }

                return arrSheet[sheetname][id];
            }

            getLinkDataByStr = function (strlink) {
                let arrs = strlink.split('_');
                let sheetname = arrs[1];
                let sheetid = arrs[2];

                return getLinkData(sheetname, sheetid);
            }

            replaceSheetID = function (linkDta) {
                console.log('replaceSheetID ', linkDta);

                let res = getLinkDataByStr(linkDta);

                return res;
            }

            replaceSheetArr = function (obj) {
                let linkdata = {};

                // console.log('replaceSheetArr', obj);

                for (let item in obj) {
                    let arrs = obj[item].split('_');

                    let ld = getLinkData(arrs[1], arrs[2]);

                    obj[arrs[2]] = ld;
                }
            }

            merge_once = function (sheetname) {
                if (mergedFlag[sheetname]) {
                    return ;
                }

                console.log('start handle ' + sheetname + ' sheet.');
                mergedFlag[sheetname] = 1;

                let keys = Object.keys(arrSheet[sheetname]);

                keys.forEach((ele) => {
                    let kkeys = Object.keys(arrSheet[sheetname][ele]);

                    kkeys.forEach((eele) => {
                        // console.log(typeof(arrSheet[sheetname][ele][eele]), arrSheet[sheetname][ele][eele]);

                        let ty = typeof (arrSheet[sheetname][ele][eele])
                        if (ty == 'string') {
                            if (arrSheet[sheetname][ele][eele].substring(0, 5) == 'link_') {
                                let linkObj = replaceSheetID(arrSheet[sheetname][ele][eele])

                                arrSheet[sheetname][ele][eele] = linkObj;
                            }
                        }
                        else if (ty == 'object') {
                            let isarr = arrSheet[sheetname][ele][eele] instanceof Array

                            if (!isarr) {
                                let tmpkeys = Object.keys(arrSheet[sheetname][ele][eele]);

                                // console.log('-ooo---', arrSheet[sheetname][ele][eele][tmpkeys[0]]);

                                if (arrSheet[sheetname][ele][eele][tmpkeys[0]].substring(0, 5) == 'link_') {
                                    replaceSheetArr(arrSheet[sheetname][ele][eele])
                                    // arrSheet[sheetname][ele][eele] = [];
                                }
                            }
                        }
                    })
                })
            }

            merge_once(defaultSheet);
        }

        excelParse.readSheet = function (worksheet) {
            reset();

            // keys
            do {
                var addr = XLSX.utils.encode_cell({ r: _data_key_line, c: _columns });
                var cell = worksheet[addr];

                if (!cell) {
                    break;
                }
                _columns++;
                _arrKeys.push(cell.v + "");

            } while (true)

            // console.log('keys', _arrKeys.length, _arrKeys);

            if (_arrKeys.length == 0) {
                return null;
            }

            // types
            for (let i = 0; i < _columns; ++i) {
                var addr = XLSX.utils.encode_cell({ r: _data_type_line, c: i });
                var cell = worksheet[addr];

                if (isComment(i)) {
                    _arrTypes.push('-');
                    continue;
                }

                // console.log(cell.v.toLowerCase());

                if (!cell || typeSupport(cell.v.toLowerCase()) == -1) {
                    _resErr = RES_DATA_FORMAT_ERR;

                    throw new Error('data type error' + _data_type_line + ' ' + i);
                }

                _arrTypes.push(cell.v.toLowerCase());
            }

            // console.log('types', _arrTypes);

            // var addr = xlsx.utils.encode_cell({ r: 7, c: 7 });
            // data
            let configData = {};
            let dataIdx = _data_begin_line;
            do {
                let tkeyaddr = XLSX.utils.encode_cell({ r: dataIdx, c: 0 });
                var tkey = worksheet[tkeyaddr];

                if (!tkey) {
                    let tkeynextaddr = XLSX.utils.encode_cell({ r: dataIdx + 1, c: 0 });
                    if (!worksheet[tkeynextaddr]) {
                        break;
                    }
                    continue;
                }

                tkvalue = getValue(tkey.v, 0);

                configData[tkvalue] = {}

                let rewardValue = {
                }

                // dataIdx 
                for (let col = 1; col < _columns; ++col) {
                    if (isComment(col)) {
                        continue;
                    }

                    let ttaddr = XLSX.utils.encode_cell({ r: dataIdx, c: col });
                    let ttvalue = _worksheet[ttaddr];

                    if (ttvalue) {
                        // console.log('--', tkvalue, _arrKeys[col], getValue(ttvalue.v, col));

                        let matchRes = checkRewardReg(_arrKeys[col]);
                        if (matchRes[0]) {
                            let idxstring = matchRes[1] + matchRes[2];

                            if (!rewardValue[idxstring]) {
                                rewardValue[idxstring] = [];
                            }
                            rewardValue[idxstring].push(getValue(ttvalue.v, col));
                        }
                        else {
                            configData[tkvalue][_arrKeys[col]] = getValue(ttvalue.v, col);
                        }
                    }
                }

                // console.log('rewardValue', rewardValue['rewardtype'].length);

                let rewardidx = 0;
                while (true) {
                    let rewardidxstr = '' + rewardidx;
                    if (rewardidx == 0) {
                        rewardidxstr = '';
                    }

                    rewardidx++;

                    if (!rewardValue['rewardtype' + rewardidxstr]) {
                        break;
                    }

                    if (rewardValue['rewardtype' + rewardidxstr].length <= 0) {
                        break;
                    }

                    if (!rewardValue['rewardid' + rewardidxstr]) {
                        rewardValue['rewardid' + rewardidxstr] = [];
                    }
                    if (!rewardValue['rewardnum' + rewardidxstr]) {
                        rewardValue['rewardnum' + rewardidxstr] = [];
                    }

                    let rewardstr = '';
                    for (let i = 0; i < rewardValue['rewardtype' + rewardidxstr].length; ++i) {
                        let aReward = rewardValue['rewardtype' + rewardidxstr][i] + '_' + rewardValue['rewardid' + rewardidxstr][i] + '_' + rewardValue['rewardnum' + rewardidxstr][i];
                        rewardstr += aReward;
                        if (i < rewardValue['rewardtype'].length - 1) {
                            rewardstr += '|';
                        }
                    }

                    configData[tkvalue]['reward' + rewardidxstr] = rewardstr;
                }

                // reward
                // if (rewardValue['rewardtype'].length > 0) {
                //     let rewardstr = '';
                //     for (let i = 0; i < rewardValue['rewardtype'].length; ++i) {
                //         let aReward = rewardValue['rewardtype'][i] + '_' + rewardValue['rewardid'][i] + '_' + rewardValue['rewardnum'][i];
                //         rewardstr += aReward;
                //         if (i < rewardValue['rewardtype'].length - 1) {
                //             rewardstr += '|';
                //         }
                //     }
                //     configData[tkvalue]['reward'] = rewardstr;
                // }

                dataIdx++;

            } while (true)

            return configData
        }

        excelParse.readExcel = function (infile, outdir) {
            try {
                const workbook = XLSX.readFile(infile, {
                    "type": "string",
                    "raw": true,
                });

                _tableName = path.basename(infile, '.xlsx');

                let arrSheetJson = {};

                const sheetNames = workbook.SheetNames;
                sheetNames.forEach((ele) => {
                    console.log("readSheet : " + ele);

                    _worksheet = workbook.Sheets[ele];

                    let sheetCfg = this.readSheet(_worksheet);

                    if (sheetCfg) {
                        arrSheetJson[ele] = sheetCfg;
                    }
                })

                let outJson = null;

                console.log('sheetNames.length', sheetNames[0]);

                if (sheetNames.length == 1) {
                    outJson = arrSheetJson[sheetNames[0]];
                }
                else {
                    this.mergeSheet(arrSheetJson, sheetNames[0]);

                    outJson = arrSheetJson[sheetNames[0]]

                    if (outJson) {
                        writeFileAsLua(outdir, outJson);
                    }

                }

                if(outJson) {
                    writeFileAsLua(outdir, outJson);
                }
            }
            catch (e) {
                _resErr = RES_EXCEL_ERR;
                throw new Error(e);
            }

            return RES_SUCCESS;
        }

        return excelParse;
    }
}

exports.ExcelParse = ExcelParse;