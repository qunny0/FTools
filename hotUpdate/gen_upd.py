#!/usr/bin/env python
#coding=utf-8

# 将newResAndSrcFile和lastResAndSrcFile,用md5做差，生成到willZipResAndSrcFile
# 用法 ./gen_upd.py 安装包版本 资源版本 大服名称
import os
import shutil
import json
import sys
import time
from hashlib import md5

scriptPath = sys.path[0]
os.chdir(scriptPath)
tmpData = os.path.join(scriptPath, "tmpData")
bigServer = os.path.join(tmpData, sys.argv[3])

print "@@@@@@@" +sys.argv[0] +sys.argv[1] +sys.argv[2] +sys.argv[3]

# 删除目录
def clearDir(dirName):
    print dirName
    if not os.path.exists(dirName):
        os.makedirs(dirName)
    else:
        shutil.rmtree(dirName)
        os.makedirs(dirName)

# 计算一个文件的md5,如果文件不存在，则返回空串
def md5_file(name):
	m = md5()
	a_file = open(name, 'rb')	#需要使用二进制格式读取文件内容
	m.update(a_file.read())
	a_file.close()
	return m.hexdigest()

# 计算两个文件的md5,返回是否相同
def compareTwoFile(file1, file2):
	if not os.path.isfile(file2):
		return False
	return md5_file(file1) == md5_file(file2)

# 复制一个文件，从file,复制到file2
# def cpFile(file1, file2):

# 创建一个文件夹，很深
def mkdir(path):
	parentPath = os.path.split(path)[0]
	if not os.path.isdir(parentPath):
		mkdir(parentPath)
	if not os.path.isdir(path):
		os.mkdir(path)
	
# 检测（遍历）一个目录
def checkDir(dirPath):
	# print("checkDir", dirPath)
	for subFile in os.listdir(dirPath):
		subFileAbsPath = os.path.join(dirPath, subFile)
		if os.path.isdir(subFileAbsPath) and (not subFile.startswith(".")):
			checkDir(subFileAbsPath)
		elif os.path.isfile(subFileAbsPath) and (not subFile.startswith(".")):
			if not compareTwoFile(subFileAbsPath, subFileAbsPath.replace("newResAndSrcFile", "lastResAndSrcFile")):
				mkdir(dirPath.replace("newResAndSrcFile", "willZipResAndSrcFile"))
				shutil.copyfile(subFileAbsPath, subFileAbsPath.replace("newResAndSrcFile", "willZipResAndSrcFile"))

# 处理updateplist
def progressUpdatePlist():
	updatePlistPath = os.path.join(bigServer, sys.argv[1])
	updatePlistPath = os.path.join(updatePlistPath, "willZipResAndSrcFile")
	updatePlistPath = os.path.join(updatePlistPath, sys.argv[1])
	updatePlistPath = os.path.join(updatePlistPath, "res")
	updatePlistPath = os.path.join(updatePlistPath, "UpdatePlist")
	if not os.path.isdir(updatePlistPath):
		return
	cmd = 'TexturePacker ' + updatePlistPath + ' --data ' + updatePlistPath + "/v" + sys.argv[2] + "_{n}plist.plist --sheet " + updatePlistPath + "/v" + sys.argv[2] + "_{n}plist.pvr.ccz" +" --allow-free-size --multipack"
	print cmd
	os.system(cmd)
	shutil.rmtree(os.path.join(updatePlistPath, "ccs"))

# 删除修改的plist，保留新加的plist（还包括pvr.ccz）
def deleteModifiedPlist():
	# 先处理updateplist
	updatePlistPath = os.path.join(bigServer, sys.argv[1])
	updatePlistPath = os.path.join(updatePlistPath, "willZipResAndSrcFile")
	updatePlistPath = os.path.join(updatePlistPath, sys.argv[1])
	updatePlistPath = os.path.join(updatePlistPath, "res")
	updatePlistPath = os.path.join(updatePlistPath, "UpdatePlist")
	updpUiImagesPath = os.path.join(updatePlistPath, "ccs")
	updpUiImagesPath = os.path.join(updpUiImagesPath, "UiImages")
	if os.path.isdir(updpUiImagesPath):
		for subFile in os.listdir(updpUiImagesPath):
			print subFile
			subFileAbsPath = os.path.join(updpUiImagesPath, subFile)
			if (not os.path.isdir(subFileAbsPath.replace("willZipResAndSrcFile","lastResAndSrcFile"))) and (not subFile.startswith(".")):
				# 如果旧项目里没有这个文件夹，就在updateplist里删掉
				print "删除 " + subFile
				shutil.rmtree(subFileAbsPath)

	# 再处理res/ccs/plist
	plistPath = os.path.join(bigServer, sys.argv[1])
	plistPath = os.path.join(plistPath, "willZipResAndSrcFile")
	plistPath = os.path.join(plistPath, sys.argv[1])
	plistPath = os.path.join(plistPath, "res")
	plistPath = os.path.join(plistPath, "ccs")
	plistPath = os.path.join(plistPath, "plist")
	if os.path.isdir(plistPath):
		for subFile in os.listdir(plistPath):
			subFileAbsPath = os.path.join(plistPath, subFile)
			if os.path.isfile(subFileAbsPath.replace("willZipResAndSrcFile","lastResAndSrcFile")) and (not subFile.startswith(".")):
				# 如果旧项目里没有这个文件夹，就在updateplist里删掉
				os.remove(subFileAbsPath)

def main():
	print "开始删除目录" + time.strftime('%Y-%m-%d %H:%M:%S')
	# print "@@@@@@@" + sys.argv[1] 
	clearDir(os.path.join(os.path.join(bigServer, sys.argv[1]), "willZipResAndSrcFile"))
	print "结束删除目录" + time.strftime('%Y-%m-%d %H:%M:%S')

	print "开始文件做差" + time.strftime('%Y-%m-%d %H:%M:%S')
	checkDir(os.path.join(os.path.join(bigServer, sys.argv[1]), "newResAndSrcFile"))
	print "结束文件做差" + time.strftime('%Y-%m-%d %H:%M:%S')
	# print "开始删除plist" + time.strftime('%Y-%m-%d %H:%M:%S')
	# 删除已经有的plist和pvrccz，只保留新加的plist和pvrccz
	# deleteModifiedPlist()
	# print "结束删除plist" + time.strftime('%Y-%m-%d %H:%M:%S')
	# print "开始合图" + time.strftime('%Y-%m-%d %H:%M:%S')
	
	# progressUpdatePlist()
	# print "结束合图" + time.strftime('%Y-%m-%d %H:%M:%S')

main()