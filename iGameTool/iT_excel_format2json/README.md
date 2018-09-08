Excel导出为Json格式。

f_excel_format2json

### 0x01 标准

#### 支持数据格式
- number
- boolean
- string
- array。默认逗号分隔符
- ++dict++

#### 表格约定规则
1. 第一行为key。
2. 第二行为类型。
3. 第三行为内容注释。
4. 默认从第4行开始为配置内容，可以指定。
5. 如果key的第一个字符为#，则改别不读取。
6. 如果个数据为空，则不导出。
7. 索引从1开始。
8. 第一列为key，如该行有数据，则不能为空。
8. 第一列连续两行为空，则表格结束。

##### 考虑
1. *指定客户端使用，或者服务器使用？*
2. *指定是否需要翻译？*

### 0x02 check point
1. 指定从第几行开始读取配置内容
2. 指定读取文件
3. 指定导出文件

### 0x03 依赖
xlsx


### 0x04 接口
```

```

### 0x05 用例
```javascript
// 指定内容从第几行开始
f_excel.setDataBeginLine(4);

/**
*   infile：输入excel格式文件
*   outfile：导出json格式
*
*   返回：
*       0：成功；
*       100：Excel读取错误；
*       101：Excel文件notfound；
*       300：指定的数据格式不支持
*       301：解释数据报错
*       400：写入文件报错
*/
var res = f_execl.export(infile, outfile);
```