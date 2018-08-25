/*
    读取一个xlsx中的指定数据转换为json格式，保存到json文件中

    1. 安装node
    2. 安装xlsx：npm install xlsx （如果安装不成功，运行npm init -f，然后再运行该命令）
*/


var XLSX = require('xlsx');
var fs = require('fs');
var path = require('path');
var util = require('util');



// var g_filepath = path.dirname(__filename) + '/';

// // config

// // 数据开始行数
// let g_data_begin_line = 3;

// exports.setDataBeginLine = (line) => {
//     this.g_data_begin_line = line;
// }

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
    ],

    createObj: function (){

        var excelParse = {};

        // 数据key所在行
        var _data_key_line = XLSX.utils.decode_row('1');

        // 数据类型所在行
        var _data_type_line = XLSX.utils.decode_row('3');

        // 数据开始行数
        var _data_begin_line = XLSX.utils.decode_row('4');

        // data_keys
        var _arrKeys = [];

        // data_types
        var _arrTypes = [];

        var _worksheet = null;

        var _columns = 0;

        var _tableName = null;

        reset = function () {
            _arrKeys = [];
            _arrTypes = [];

            _worksheet = null;

            _columns = 0;

            _tableName = null;
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

            throw new Error(idx + ' - ' + v);
        }

        isComment = function (idx) {
            return _arrKeys[idx].indexOf('#') == 0
        }

        handleExcel = function (infile) {
            try {
                const workbook = XLSX.readFile(infile, {
                    "type": "string",
                    "raw": true,
                });
                const sheetNames = workbook.SheetNames;

                _worksheet = workbook.Sheets[sheetNames[0]];

                _tableName = sheetNames[0];
            }
            catch (e) {
                throw new Error(e);
                process.exit(RES_EXCEL_ERR);
            }

            // keys
            do {
                var addr = XLSX.utils.encode_cell({ r: _data_key_line, c: _columns });
                var cell = _worksheet[addr];

                if (!cell) {
                    break;
                }

                _columns++;

                _arrKeys.push(cell.v);
            } while(true)

            // types
            for (let i = 0; i < _columns; ++i) {
                var addr = XLSX.utils.encode_cell({ r: _data_type_line, c: i });
                var cell = _worksheet[addr];

                if (isComment(i)) {
                    _arrTypes.push('-');
                    continue;
                }

                if (!cell || ExcelParse.supportType.indexOf(cell.v.toLowerCase()) == -1) {
                    process.exit(RES_DATA_FORMAT_ERR);
                }

                _arrTypes.push(cell.v.toLowerCase());
            }

            console.log('keys', _arrKeys);
            console.log('types', _arrTypes);

            // var addr = xlsx.utils.encode_cell({ r: 7, c: 7 });
            // data
            let configData = {};
            let dataIdx = _data_begin_line;
            do {
                let tkeyaddr = XLSX.utils.encode_cell({ r: dataIdx, c: 0 });
                var tkey = _worksheet[tkeyaddr];

                if (!tkey) {
                    let tkeynextaddr = XLSX.utils.encode_cell({ r: dataIdx+1, c: 0 });
                    if (!_worksheet[tkeynextaddr]) {
                        break;
                    }
                    continue;
                }
                
                tkvalue = getValue(tkey.v, 0);

                configData[tkvalue] = {}

                // dataIdx 
                for (let col = 1; col < _columns; ++col) {
                    if (isComment(col)) {
                        continue ;
                    }

                    let ttaddr = XLSX.utils.encode_cell({ r: dataIdx, c: col });
                    let ttvalue = _worksheet[ttaddr];

                    if (ttvalue) {
                        configData[tkvalue][_arrKeys[col]] = getValue(ttvalue.v, col);
                    }
                }

                dataIdx++;

            } while (true)

            // console.log('configData', configData);


            return configData
        }

        writeFile = function (outdir, cfgdata) {

            var outfile = path.normalize(outdir + '/' + _tableName + '.json');

            var outputDir = path.basename(outfile);

            if (!fs.existsSync(outputDir)) {
                fs.mkdirSync(outputDir);
            }

            let jsondata = JSON.stringify(cfgdata);

            console.log(jsondata);

            fs.writeFileSync(outfile, jsondata);
        }

        excelParse.setDataBeginLine = function (v) {
            _data_begin_line = XLSX.utils.decode_row('' + v);
        }

        excelParse.getDataBeginLine = function () {
            return _data_begin_line;
        }

        excelParse.export2 = function (infile, outdir) {
            reset();

            console.log(infile, outdir);

            if (!fs.existsSync(infile)) {
                process.exit(RES_EXCEL_NOTFOUND);
            }


            let configData = handleExcel(infile);

            writeFile(outdir, configData);
        }

        return excelParse;
    }
}

let ep = ExcelParse.createObj();

ep.setDataBeginLine(4);

let res = ep.export2('/Users/ben/Downloads/Trigger.xlsx', '/Users/ben/Desktop/t/');

console.log('res', res);