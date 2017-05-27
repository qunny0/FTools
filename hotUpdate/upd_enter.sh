#!/bin/bash

# 统一的入口

DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR

# 用法 ./upd_enter.sh 参数1 参数2 参数3
# 参数1 大服名 	 	bigServer
# 参数2 语言 			language
# 参数3 安装包版本 	packageVersion
# 资源版本    resVersion
# 更新包目录 	updPath

bigServer=$1
updPath="../updPackageFile/$bigServer"
packageVersion=$3
language=$2

source profile.in
echo "开始svn更新"
date

# 初始化项目文件
if [[ ! -d "../TankWar1" ]]; then
	mkdir "../TankWar1"
	mkdir "../TankWar1/Resources/"
	cd ../TankWar1/
	svn checkout http://$usr@svn.raysns.com/repos/modernwarfare/client/branches/GermanyBranch/projects/Tank/Resources --username $usr --password $pwd
	svn checkout http://$usr@svn.raysns.com/repos/modernwarfare/client/branches/GermanyBranch/projects/Tank/ResEmpireWar --username $usr --password $pwd
	cd $DIR
fi
if [[ ! -d "../TankWar2" ]]; then
	mkdir "../TankWar2"
	mkdir "../TankWar2/Resources/"
	cd ../TankWar2/
	svn checkout http://$usr@svn.raysns.com/repos/modernwarfare/client/branches/GermanyBranch/projects/Tank/Resources --username $usr --password $pwd
	svn checkout http://$usr@svn.raysns.com/repos/modernwarfare/client/branches/GermanyBranch/projects/Tank/ResEmpireWar --username $usr --password $pwd
	cd $DIR
fi
cd $DIR

# 更新 zip文件及svn.txt
if [[ ! -d "../updPackageFile" ]]; then
	mkdir "../updPackageFile"
fi
if [[ ! -d "../updPackageFile/$bigServer" ]]; then
	cd ../updPackageFile/
	svn checkout http://$usr@publish.rayjoy.com/repos/modernwar/publish/client/europe/tankheroclient/updPackageFile/$bigServer --username $usr --password $pwd
	if [ $? -ne 0 ];then
		echo "svn checkout updPackageFile 失败"
		exit 1
	fi
	cd $DIR
fi

cd ../updPackageFile/$bigServer
echo "更新updPackageFile start $bigServer"
pwd
svn cleanup
svn update --username $usr --password $pwd

echo "after update $bigServer -- "

if [ $? -ne 0 ];then
	echo "更新updPackageFile"
	exit 1
fi
cd $DIR

# 版本号
resVersion=$[$( cat $updPath/svnfiles/upd/commonVersion.php | grep "return" |awk '{print $NF}'|awk -F';' '{print $1}' )+1]
oldResVersion=$[$resVersion-1]
echo "resVersion $resVersion"
svnVersion=$( cat $updPath/svnfiles/upd/$packageVersion/$oldResVersion/svn.txt )
echo "svn $svnVersion"
echo "获取更新的svn版本号 "

resDiffSvn=$( cat $updPath/svnfiles/updtest/$packageVersion/resdiffsvn.txt )
# 处理last
# 更新TankWar1
cd ../TankWar1/Resources
pwd
svn info

echo "resDiffSvn $resDiffSvn -----"

svn cleanup --username $usr --password $pwd

echo "----- switch $svnVersion $usr bbbbbb"

svn switch http://$usr@svn.raysns.com/repos/modernwarfare/client/branches/GermanyBranch/projects/Tank/Resources -r$svnVersion --username $usr --password $pwd
if [ $? -ne 0 ];then
	echo "生成更新包失败"
	exit 1
fi
echo "1111111更新TankWar1的Resources"
cd $DIR

cd ../TankWar1/ResEmpireWar
pwd
svn info
svn cleanup --username $usr --password $pwd
svn switch http://$usr@svn.raysns.com/repos/modernwarfare/client/branches/GermanyBranch/projects/Tank/ResEmpireWar -r$resDiffSvn --username $usr --password $pwd
if [ $? -ne 0 ];then
	echo "生成更新包失败"
	exit 1
fi
echo "33333333更新TankWar1的ResEmpireWar"
cd $DIR
./check_current_files.sh $bigServer $language $packageVersion lastResAndSrcFile 1


# 处理new
cd ../TankWar2/Resources
svn cleanup
svn switch http://$usr@svn.raysns.com/repos/modernwarfare/client/branches/GermanyBranch/projects/Tank/Resources --username $usr --password $pwd
if [ $? -ne 0 ];then
	echo "1111111生成更新包失败"
	exit 1
fi
echo "22222222更新TankWar2的Resources"
cd $DIR

cd ../TankWar2/ResEmpireWar
svn cleanup
svn switch http://$usr@svn.raysns.com/repos/modernwarfare/client/branches/GermanyBranch/projects/Tank/ResEmpireWar --username $usr --password $pwd
if [ $? -ne 0 ];then
	echo "生成更新包失败"
	exit 1
fi
echo "44444444更新TankWar1的ResEmpireWar"
cd $DIR
./check_current_files.sh $bigServer $language $packageVersion newResAndSrcFile 2

if [[ "$(type -t TexturePacker)abc" == "abc" ]]; then
	echo "未安装TexturePacker"
	exit 1
fi

echo "结束svn更新"
date


echo "开始gen_upd"
date

# md5做差
./gen_upd.py $packageVersion $resVersion $bigServer
if [[ ! -d "./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile/luascript" ]]; then
	echo "文件没有任何变动，无法制作更新包。"
	echo $packageVersion
	echo $resVersion
	echo $bigServer
	exit 1
fi

if [[ "$(type -t TexturePacker)abc" == "abc" ]]; then
	echo "未安装TexturePacker"
	exit 1
fi

tmpResDiff="./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile/luascript/ResEmpireWar"
if [[ -d $tmpResDiff ]]; then
	./compress_fragment.py $resVersion $tmpResDiff
	./compress_fragment_copy2zip.py $bigServer $packageVersion $resVersion
fi
echo "结束gen_upd"
date
#
#
echo "开始编译lua"
date
# 编译lua文件
./compile_newlua.sh $bigServer $packageVersion

echo "结束编译lua"
date

echo "开始zip"
date
# 生成更新包
./zip_upd.sh $bigServer $packageVersion $resVersion

echo "结束zip"
date
if [[ ! -d "$updPath/svnfiles/updtest/$packageVersion/$resVersion" ]]; then
	mkdir "$updPath/svnfiles/updtest/$packageVersion/$resVersion"
fi
# 记录svn号
# cd ../TankWar2/ResEmpireWar
#svnResources=`svn info ../TankWar2/Resources |grep Revision: |awk '{printf $2}'`
#svnResEmpireWar=`svn info ../TankWar2/ResEmpireWar |grep Revision: |awk '{printf $2}'`

svnResources=`svn info ../TankWar2/Resources |grep 最后修改的版本: |awk '{printf $2}'`
svnResEmpireWar=`svn info ../TankWar2/ResEmpireWar |grep 最后修改的版本: |awk '{printf $2}'`


echo "写入更新之后的svn版本号 $svnResources $svnResEmpireWar"
echo $svnResources
echo $svnResEmpireWar
if [ $svnResources -gt $svnResEmpireWar ]
then
   echo $svnResources > $updPath/svnfiles/updtest/$packageVersion/$resVersion/svn.txt
else
   echo $svnResEmpireWar > $updPath/svnfiles/updtest/$packageVersion/$resVersion/svn.txt
fi
# svn info ../TankWar2/Resources |grep Revision: |awk   '{printf $2}' > $updPath/svnfiles/updtest/$packageVersion/$resVersion/svn.txt
# svn info ../TankWar2/Resources |grep Revision: |awk   '{printf $2}' > $updPath/svnfiles/updtest/$packageVersion/$resVersion/svn.txt
