#/usr/bin/python
#-*-coding:utf-8-*-

import sys
import xlrd
import xlwt

reload(sys)
sys.setdefaultencoding('utf8')

textencoding = "utf-8"

# 日期
# 品牌名
# 商家bd
# 蜂窝
# 商家id
# 商家名
# 配送折扣
# 原价交易额
# 实际支付交易额
# 推单数
# 订单数
# 活动订单数
# 单均价
# 首购用户数
# 配送费
kFDDate = 0
kFDBrandName = 1
kFDAddress = 2
kFDShopID = 3
kFDShopName = 4
kFDDisaccount = 5
kFDOriginalPrice = 6
kFDFactPrice = 7
kFDRecommendOrders = 8
kFDOrders = 9
kFDActivityOrders = 10
kFDAveragePrice = 11
kFDFirstUsers = 12
kFDFreight = 13

# kT1Idx = 1
# kT1Name = u"凉皮"
#
# kT2Idx = 2
# kT2Name = u"虾饭"
#
# kT1Count = 0
# kT2Count = 0

kTypes = [u"凉皮", u"虾饭", u"鸡", u"麻辣烫", u"面", u"饺子"]

G_TypeData = {}

G_excelData = {}

def handleShopName():
    # for i in range(len(kTypes)):
    #     print kTypes[i]

    global G_TypeData

    for k in G_excelData:
        for kk in G_excelData[k]:
            if kk == kFDShopName:
                for i in range(len(kTypes)):
                    if G_excelData[k][kk].find(kTypes[i]) != -1:
                        if not G_TypeData.has_key(kTypes[i]):
                            G_TypeData[kTypes[i]] = []
                        G_TypeData[kTypes[i]].append(G_excelData[k][kk])

    for k in G_TypeData:
        print k + " -- : " + str(len(G_TypeData[k]))
        for i in range(len(G_TypeData[k])):
            print "\t"+G_TypeData[k][i]


def main():
    path="/Users/fubei/Documents/git/FTools/python/xiaoliansuoshangjia.xls"
    # path = "/Users/ben/Code/python/xiaoliansuoshangjia.xls"
    data = xlrd.open_workbook(path)
    table = data.sheets()[0]

    rows = table.nrows
    cols = table.ncols

    global G_excelData
    G_excelData = {}

    print rows
    print cols

    print "---------------"
    print table.cell(0,0).value
    print "---------------"

    for i in range(rows):
        G_excelData[i] = {}
        for j in range(cols):
            G_excelData[i][j] = table.cell(i,j).value

    handleShopName()

    # for k in G_excelData:
    #     for kk in G_excelData[k]:
    #         if kk == kFDShopName:
    #             if G_excelData[k][kk].find(kT1Name) != -1:
    #                 pass
                # if excelData[k][kk].find(kT1Name) != -1:
                #     print excelData[k][kk]
                #     global kT1Count
                #     kT1Count = kT1Count + 1
                # elif excelData[k][kk].find(kT2Name) != -1:
                #     print excelData[k][kk]
                #     global kT2Count
                #     kT2Count = kT2Count + 1

    # print kT1Name + str(kT1Count)
    # print kT2Name + str(kT2Count)

if __name__ == "__main__":
    main()
