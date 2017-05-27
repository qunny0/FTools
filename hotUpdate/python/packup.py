#-*-coding:utf-8-*-

from updUtil import *
from termcolor import *

import os

LANGUAGE=''
PACKAGE_VERSION=''
UPD_PATH = ''
SVN_ACCOUNT = ''

CURRENT_DIR = ''


# 处理碎图资源
def handleFragmentRes():
	oldFragRes = "../Resource1/"
	newFragRes = "../Resource2/"

	svnInfo = G_getValue('svnInfo')
	svnPath = svnInfo['path']
	svnUsr = svnInfo['usr']
	svnPassword = svnInfo['password']
	svnFullPath = svnPath%(svnUsr)
	fragmentResSVNPath = svnFullPath + "/projects/Tank/Resources"

	if not os.path.exists(oldFragRes):
		os.makedirs(oldFragRes)
		os.chdir(oldFragRes)

		svnCmd = "svn checkout " + fragmentResSVNPath + " --username " + svnUsr + " --password " + svnPassword
		print svnCmd
		uu_executeProcess(svnCmd)

	if not os.path.exists(newFragRes):
		os.makedirs(newFragRes)
		os.chdir(newFragRes)

		svnCmd = "svn checkout " + fragmentResSVNPath + " --username " + svnUsr + " --password " + svnPassword
		print svnCmd
		uu_executeProcess(svnCmd)

	os.chdir(CURRENT_DIR)


def updateUpdVersionRecord:
	updatePath = "../updateFile"
	if not os.path.exists(updatePath):
		os.makedirs(updatePath)

	svnInfo = G_getValue('svnInfo')
	svnUpdPath = svnInfo['updPath']
	svnUsr = svnInfo['usr']
	svnPassword = svnInfo['password']
	svnFullPath = svnUpdPath%(svnUsr)

	updateServerPath = updatePath + G_getValue("bigServer")
	if not os.path.exists(updateServerPath):
		os.chdir(updatePath)

		svnCmd = "svn checkout " + svnFullPath + " --username " + svnUsr + " --password " + svnPassword
		print svnCmd
		uu_executeProcess(svnCmd)

	print colored("!!!!! [update  : " + updateServerPath + "] ", "green")
	os.chdir(updateServerPath)
	uu_executeCommand("svn cleanup")
	uu_executeCommand("svn update " + " --username " + svnUsr + " --password " + svnPassword)

	os.chdir(CURRENT_DIR)


def handleUpdate:
	# 版本号
	resVersion=$[$( cat $updPath/svnfiles/upd/commonVersion.php | grep "return" |awk '{print $NF}'|awk -F';' '{print $1}' )+1]
	oldResVersion=$[$resVersion-1]
	echo "resVersion $resVersion"
	svnVersion=$( cat $updPath/svnfiles/upd/$packageVersion/$oldResVersion/svn.txt )
	echo "svn $svnVersion"
	echo "获取更新的svn版本号 "



def package(_packageVersion):
	global PACKAGE_VERSION
	global CURRENT_DIR

	# CURRENT_DIR = os.getcwd()
	CURRENT_DIR = os.path.dirname(os.path.abspath("__file__"))
	PACKAGE_VERSION = _packageVersion

	print colored("begin package : " + str(PACKAGE_VERSION), "green")
	print "---------- handle fragment resource ---------- " + str(PACKAGE_VERSION)

	handleFragmentRes()

	updateUpdVersionRecord()
