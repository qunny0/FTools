#/usr/bin/python
#-*-coding:utf-8-*-

import sys
import xlrd
import xlwt

def main():
    path = "/Users/ben/Code/python/xiaoliansuoshangjia.xls"
    data = xlrd.open_workbook(path)
    table = data.sheets()[0]

    rows = table.nrows
    cols = table.ncols

    excelData = {}

    print rows
    print cols

    print "---------------"
    print table.cell(0,0).value
    print "---------------"

    for i in range(rows):
        excelData[i] = {}
        for j in range(cols):
            excelData[i][j] = table.cell(i,j).value

    for k in excelData:
        if k == 1:
            for kk in excelData[k]:
                print excelData[k][kk]



if __name__ == "__main__":
    main()
