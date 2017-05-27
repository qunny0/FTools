#!/usr/bin/env python
#-*- coding: utf-8 -*-

import os
import sys
import shutil

standard_out = sys.stdout

# 版本号
baseVersion = sys.argv[1]
# 碎图差异路径
fragmentRes = sys.argv[2]

print(" -- baseVersion : " + baseVersion)
print(" -- fragmentRes : " + fragmentRes)

CURRENT_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__),os.path.pardir))
ABS_PATH = os.path.abspath(os.path.dirname(__file__))
FRAMECACHE_PLIST_LIST = "plist_only_in_startgame"

print(" -- current_dir : " + CURRENT_DIR)

print("\n")

G_STARTGAME = "startGame.lua"
# 存储仅在startGame中加载的图片
g_plist_in_startgame = [
]
g_plist_not_in_startgame = [
]

OUTPUT_PATH = "./"

TextureTypePng = [
]

TextureFormat8888 = [
	"homeBuilding",
	"newUnCompress",
	"clickBuilding",
]

SKIP_LIST = ["DS_Store","tmp","svn","plist","fnt"]

compress_t_4444 = 1		# 4444
compress_t_8888 = 2		# 8888
g_compress_t_type = 1


def checkListWhetherComment(line):
	strtrip = line.strip()
	if strtrip.find("--") == 0:
		return True
	return False

def getPreLoadImgList(luafile):
	relPath = luafile[luafile.find("Resources"): len(luafile)]
	reloutput = False

	st_index = relPath.find(G_STARTGAME)
	pushToStartList = False
	if st_index != -1 and len(g_plist_in_startgame) == 0:
		pushToStartList = True

	f = open(luafile, "r")
	lines = f.readlines()
	f.close()

	for line in lines:
		if checkListWhetherComment(line):
			continue

		if line.find("addSpriteFramesWithFile") != -1 :
			left = line.find("\"")
			right = line.rfind("\"")
			if left != -1 and right != -1:
				plistname = line[left+1: right]
				filename = plistname[plistname.rfind("/") + 1: plistname.find(".")]

				if pushToStartList:
					# print("-- add " + filename)
					g_plist_in_startgame.append(filename)
				else:
					if st_index == -1 and g_plist_in_startgame.count(filename) > 0:
						print("-- remove " + relPath + " >> " + filename)
						g_plist_in_startgame.remove(filename)

				if not reloutput:
					reloutput = True
					# print(relPath)
				# print("\t\t" + plistname)


def travelLuaDir(rootLua):
	names = os.listdir(rootLua)

	# travel source files
	for name in names:
		if checkSkip(name):
			continue

		srcName = os.path.join(rootLua, name)

		try:
			# if is directory then recursion copy or copy files
			if not os.path.isdir(srcName):
				if name[name.find(".") + 1:len(name)] == "lua":
					getPreLoadImgList(srcName)
			else:
				travelLuaDir(srcName)

		except:
			raise


# 遍历各lua中读取的plist。找的只有在startGame中加载的plist
def findPlistOnlyStartgame(respath):
	# print("116 -- " + respath)

	getPreLoadImgList(respath+"startGame.lua")

	travelLuaDir(respath)

	print("[plist_file] 118!!" + ABS_PATH + "/" + FRAMECACHE_PLIST_LIST)
	f = open(ABS_PATH + "/" + FRAMECACHE_PLIST_LIST, "w")
	content = ""
	for ele in g_plist_in_startgame:
		print(ele)
		content = content + ele + "\n"

	f.write(content)
	f.close()

	sys.stdout = standard_out


def checkSkip(_path):
	name = _path.split('.')[-1]
	for x in SKIP_LIST:
		if x == name:
			return True
	return False


def deleteSpecialLine(tgtFile):
	f = open(tgtFile, "r")
	lines = f.readlines()
	f.close()

	f = open(tgtFile, "w")
	for line in lines:
		if line.find("SmartUpdate") == -1 and line.find("smartupdate") == -1:
			f.write(line)
	f.close()


def getFileFormat(filepath):
	tgtname = filepath.split('/')[-1]
	for tex in TextureFormat8888:
		if tex == tgtname:
			return compress_t_8888
	return compress_t_4444


def isAddInStartgame(name):
	for ele in g_plist_in_startgame:
		if ele == name:
			return  True
	return False


def removeDir(filepath):
	print("remove  -> " + filepath)
	if os.path.isdir(filepath):
		shutil.rmtree(filepath)


def dir_copyTree(src, dst):
	names = os.listdir(src)

	# if target file is not exist. create directory
	if not os.path.exists(dst):
		os.makedirs(dst)

	# travel source files
	for name in names:
		if checkSkip(name):
			continue

		srcName = os.path.join(src, name)
		# dstName = os.path.join(dst, name)

		if os.path.isdir(srcName) and not isAddInStartgame(name):
			continue

		try:
			# if is directory then recursion copy or copy files
			if os.path.isdir(srcName):
				if getFileFormat(srcName) == g_compress_t_type:
					dir_copyTree(srcName, dst)
			else:
				# if not os.path.exists(dst):
				# print("" + srcName + " --> " + dst)
				shutil.copy2(srcName, dst)
		except:
			# error.traceback()
			raise


def runCmd(_cmd):
	cmdline = os.popen(_cmd)
	while 1:
		opt = cmdline.readline()
		if opt == "":
			break


def compressPic(src_dir, tgt_dir):
	cmd = "TexturePacker {0} --data {1} --sheet {2} --max-width 2048 --max-height 2048 --disable-rotation --force-publish --allow-free-size --shape-padding 2 --border-padding 0 --premultiply-alpha --trim-mode None --dither-fs-alpha --multipack --opt {3}"
	tgtName = src_dir.split('/')[-1] + ""
	name = tgtName + "{n}"
	imgFormat = "RGBA4444"
	if g_compress_t_type == compress_t_8888:
		imgFormat = "RGBA8888"

	data_filename = os.path.join(tgt_dir, name + ".plist")
	texture_file = os.path.join(tgt_dir, name + ".pvr.ccz")
	cmd_texture = cmd.format(src_dir, data_filename, texture_file, imgFormat)

	runCmd((cmd_texture))

	# 删除SmartUpdate
	_s = 0
	while(True):
		tmpName = tgtName + str(_s)
		_s = _s + 1
		datapath = os.path.join(tgt_dir, tmpName + ".plist")
		if os.path.isfile(datapath):
			deleteSpecialLine(datapath)
		else:
			break


def handleTexture(compressType):
	global g_compress_t_type
	g_compress_t_type = compressType

	# + baseVersion
	dstpath = OUTPUT_PATH + "upd_pic_4444_"
	if g_compress_t_type == compress_t_8888:
		dstpath = OUTPUT_PATH + "upd_pic_8888_"

	# if target file is not exist. create directory
	if not os.path.exists(dstpath):
		os.makedirs(dstpath)

	srcpath = fragmentRes
	print("[" + srcpath + " --> " + dstpath + "]")
	dir_copyTree(srcpath, dstpath)

	compressPic(dstpath, OUTPUT_PATH+"update_pic")
	removeDir(dstpath)


if __name__ == '__main__':
	findPlistOnlyStartgame("../TankWar2/Resources/")

	removeDir(OUTPUT_PATH+"update_pic")

	print("\n\n\n handleTexture 4444")
	handleTexture(compress_t_4444)
	print("~~~~~~~~~~~~ complete handleTexture 4444 ! ~~~~~~~~~~~~")

	print("\n\n\n handleTexture 8888")
	handleTexture(compress_t_8888)
	print("~~~~~~~~~~~~ complete handleTexture 8888 !~~~~~~~~~~~~")

