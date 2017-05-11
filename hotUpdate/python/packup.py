#-*-coding:utf-8-*-

from updUtil import *
from termcolor import *

import os

BIG_SERVER=''
LANGUAGE=''
PACKAGE_VERSION=''
UPD_PATH = ''
SVN_ACCOUNT = ''

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
	oldFragRes = "../resource1/"
	newFragRes = "../resource2"

	svnInfo = G_getValue('svnInfo')
	svnPath = svnInfo['path']
	svnUsr = svnInfo['usr']
	svnPassword = svnInfo['password']
	svnFullPath = svnPath%(svnUsr)
	fragmentResSVNPath = svnFullPath + "/projects/Tank/ResEmpireWar"

	if not os.path.exists(oldFragRes):
		os.makedirs(oldFragRes)
		os.chdir(oldFragRes)

		svnCmd = "svn checkout " + fragmentResSVNPath + " --username " + svnUsr + " --password " + svnPassword
		print svnCmd
		uu_executeProcess(svnCmd)
		# uu_executeCommand(svnCmd)

	# print svnFullPath

	# os.chdir(CURRENT_DIR)

def package(_packageVersion):
	global PACKAGE_VERSION
	global CURRENT_DIR

	CURRENT_DIR = os.getcwd()
	PACKAGE_VERSION = _packageVersion

	print colored("begin package : " + str(PACKAGE_VERSION), "green")

	handleFragmentRes()
