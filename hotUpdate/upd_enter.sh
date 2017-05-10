#!/bin/bash

# 统一的入口

DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR

# 用法 ./upd_enter.sh 参数1 参数2 参数3
# 参数1 大服名 	 		bigServer
# 参数2 语言 			language
# 参数3 安装包版本 		packageVersion
# 资源版本    			resVersion
# 更新包目录 				updPath

bigServer=$1
updPath="../sdk_pub/$bigServer"
packageVersion=$3
language=$2

source profile.in
echo "开始svn更新"
date

# 初始化项目文件
if [[ ! -d "../TankWar1/Resources/" ]]; then
	mkdir "../TankWar1"
	mkdir "../TankWar1/Resources/"
	cd ../TankWar1/
	svn checkout http://$usr@svn.raysns.com/repos/modernwarfare/client/branches/TencentBranch/projects/Tank/Resources --username $usr --password $pwd
	cd $DIR
fi
if [[ ! -d "../TankWar2/Resources/" ]]; then
	mkdir "../TankWar2"
	mkdir "../TankWar2/Resources/"
	cd ../TankWar2/
	svn checkout http://$usr@svn.raysns.com/repos/modernwarfare/client/branches/TencentBranch/projects/Tank/Resources --username $usr --password $pwd
	cd $DIR
fi
cd $DIR

# 更新 zip文件及svn.txt
if [[ ! -d "../sdk_pub" ]]; then
	mkdir "../sdk_pub"
fi
if [[ ! -d "../sdk_pub/$bigServer" ]]; then
	cd ../sdk_pub/
	svn checkout http://$usr@publish.rayjoy.com/repos/modernwar/publish/client/test/tankheroclient/modernwar/sdk_pub/$bigServer --username $usr --password $pwd
	if [ $? -ne 0 ];then
		echo "svn checkout 失败"
		exit 1
	fi
	cd $DIR
fi
cd ../sdk_pub/$bigServer
echo "更新zip和svn.txt"
pwd
svn cleanup
svn update --username $usr --password $pwd
if [ $? -ne 0 ];then
	echo "生成更新包失败"
	exit 1
fi
cd $DIR

# 版本号
resVersion=$[$( cat $updPath/upd/commonVersion.php | grep "return" |awk '{print $NF}'|awk -F';' '{print $1}' )+1]
oldResVersion=$[$resVersion-1]
echo "resVersion $resVersion"
svnVersion=$( cat $updPath/upd/$packageVersion/$oldResVersion/svn.txt )
echo "svn $svnVersion"
echo "00000000 "
# 处理last
# 更新TankWar1
cd ../TankWar1/Resources
pwd
svn info
svn cleanup --username $usr --password $pwd
svn update -r$svnVersion --username $usr --password $pwd
echo "after update -r$svnVersion"
if [ $? -ne 0 ];then
	echo "生成更新包失败"
	exit 1
fi
echo "1111111更新TankWar1"
cd $DIR
./check_current_files.sh $bigServer $language $packageVersion lastResAndSrcFile 1

# 处理new
cd ../TankWar2/Resources
svn cleanup
svn update --username $usr --password $pwd
if [ $? -ne 0 ];then
	echo "生成更新包失败"
	exit 1
fi
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

echo "结束gen_upd"
date


# 处理碎图文件
./upd_enter_for_res.sh $bigServer $language $packageVersion



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
if [[ ! -d "$updPath/updtest/$packageVersion/$resVersion" ]]; then
	mkdir "$updPath/updtest/$packageVersion/$resVersion"
fi

# # 记录svn号
# svn info ../TankWar2/Resources |grep Revision: |awk   '{printf $2}' > $updPath/updtest/$packageVersion/$resVersion/svn.txt
