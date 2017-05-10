#-*-coding:utf-8-*-

from updUtil import *
from termcolor import *

import os

BIG_SERVER=''
LANGUAGE=''
PACKAGE_VERSION=''
UPD_PATH = ''

CURRENT_DIR = ''


# _, o = uu_executeCommand('ls')

#
#
# bigServer=$1
# updPath="../sdk_pub/$bigServer"
# packageVersion=$3
# language=$2
#
# echo "bigServer : $bigServer"
# echo "updPath : $updPath"
# echo "packageVersion : $packageVersion"
# echo "language : language"
#
# source profile.in
# echo "开始svn更新"
# date
#
# # 初始化项目文件
# if [[ ! -d "../TankWar1/ResEmpireWar/" ]]; then
# 	mkdir "../TankWar1"
# 	mkdir "../TankWar1/ResEmpireWar/"
# 	cd ../TankWar1/
# 	svn checkout http://$usr@svn.raysns.com/repos/modernwarfare/client/branches/TencentBranch/projects/Tank/ResEmpireWar --username $usr --password $pwd
# 	cd $DIR
# fi

# 处理碎图资源
def handleFragmentRes():
	oldFragRes = "../resource1"
	newFragRes = "../resource2"

	# os.makedirs(oldFragRes)

	if not os.path.exists(oldFragRes):
		os.makedirs(oldFragRes)


	# os.chdir(CURRENT_DIR)

def package(_bigServer, _language, _packageVersion):

	global BIG_SERVER
	global LANGUAGE
	global PACKAGE_VERSION
	global CURRENT_DIR

	BIG_SERVER = _bigServer
	LANGUAGE = _language
	PACKAGE_VERSION = _packageVersion
	UPD_PATH = "../updPackageFile/" + BIG_SERVER + "/"

	print colored("begin package : " + BIG_SERVER + "  " + LANGUAGE + "  " + str(PACKAGE_VERSION) + "  " + UPD_PATH, "green")

	CURRENT_DIR = os.getcwd()

	_, o = uu_executeCommand('source svnAccount.in')

	handleFragmentRes()
