#!/usr/bin/env python
#-*- coding: utf-8 -*-

import os
import sys
import shutil

bigServer = sys.argv[1]
packageVersion = sys.argv[2]
resVersion = sys.argv[3]

print(" -- bigServer : " + bigServer)
print(" -- packageVersion : " + packageVersion)
print(" -- resVersion : " + resVersion)

# 存储仅在startGame中加载的图片
g_plist_in_startgame = [
]

def plistInStartgame(filename):
    for ele in g_plist_in_startgame:
        if ele == filename:
            return True
    return False


def dir_copyTree(src, dst):
    if not os.path.exists(src):
        return 

    names = os.listdir(src)

    # if target file is not exist. create directory
    if not os.path.exists(dst):
		os.makedirs(dst)

    # travel source files
    for name in names:
        srcName = os.path.join(src, name)
        dstName = os.path.join(dst, name)

        if os.path.isdir(srcName) and not isAddInStartgame(name):
            continue

        try:
            # if is directory then recursion copy or copy files
            if os.path.isdir(srcName):
                if getFileFormat(srcName) == g_compress_t_type:
                    dir_copyTree(srcName, dstName)
            else:
                if not os.path.exists(dstName):
                    print("" + srcName + " --> " + dst)
                    shutil.copy2(srcName, dst)
        except:
            # error.traceback()
            raise            


def deletefile(filedir):
    print("remove file -> " + filedir)
    os.remove(filedir)


def deletePlistInStartgame(delepath):
    names = os.listdir(delepath)

    # travel source files
    for name in names:
        srcName = os.path.join(delepath, name)

        try:
            # if is directory then recursion copy or copy files
            if not os.path.isdir(srcName):
                extname = name[name.find(".") + 1:len(name)]
                filename = name[0:name.find(".")]
                if extname == "plist" or extname == "pvr.ccz" :
                    if plistInStartgame(filename):
                        deletefile(srcName)
            else:
                deletePlistInStartgame(srcName)
        except:
            raise


def copyUpdateTooZip():
    updPicPath = "./update_pic/"
    zippath = "./tmpData/" + bigServer + "/" + packageVersion + "/willZipResAndSrcFile/luascript/Resources/boatImage/upd_pic"
    print("85 " + updPicPath + " -> " + zippath)
    dir_copyTree(updPicPath, zippath)


def main():
    f = open("./plist_only_in_startgame", "r")
    lines = f.readlines()
    f.close()

    for line in lines:
        g_plist_in_startgame.append(line[0:-1])

    zippath = "./tmpData/" + bigServer + "/" + packageVersion + "/willZipResAndSrcFile/luascript"
    deletePlistInStartgame(zippath)

    copyUpdateTooZip()


if __name__ == '__main__':
    main()
