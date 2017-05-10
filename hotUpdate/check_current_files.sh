#!/bin/bash

# 从前端工程检出当前文件
DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR

# 用法 ./check_current_files.sh 大服名 语言 安装包版本 检出到的目录(只有名称，没有路径) 工程源（1或2）

projPath="../TankWar$5/Resources"
bigServer=$1
language=$2
packageVersion=$3
toPath=$4

# if [[ "$(svn diff $1/src)" -ne "" ]]; then
# 	echo "本地代码与svn不一致"
# 	exit 1
# fi
if [ -d "./tmpData/$bigServer/$packageVersion/$toPath" ]; then
	rm -rf ./tmpData/$bigServer/$packageVersion/$toPath
fi
mkdir ./tmpData
mkdir ./tmpData/$bigServer
mkdir ./tmpData/$bigServer/$packageVersion
mkdir ./tmpData/$bigServer/$packageVersion/$toPath
# mkdir ./tmpData/$bigServer/$packageVersion/$toPath/$packageVersion
mkdir ./tmpData/$bigServer/$packageVersion/$toPath/luascript



echo "开始处理文件 check_current_files"
date

cp -rf $projPath/ ./tmpData/$bigServer/$packageVersion/$toPath/luascript/
# cp -rf $projPath/ ./tmpData/$bigServer/$packageVersion/$toPath/$packageVersion/
# cp -rf $projPath/res ./tmpData/$bigServer/$packageVersion/$toPath/$packageVersion/
# if [ -d "./$language" ]; then
# 	echo "error: ./$language 已存在"
# 	exit 1
# fi
# mv -f ./tmpData/$bigServer/$packageVersion/$toPath/$packageVersion/res/languageRes/$language ./$language
# rm -rf ./tmpData/$bigServer/$packageVersion/$toPath/$packageVersion/res/languageRes/*
# mv -f ./$language ./tmpData/$bigServer/$packageVersion/$toPath/$packageVersion/res/languageRes/$language
# mkdir ./tmpData/$bigServer/$packageVersion/$toPath/$packageVersion/res/UpdatePlist
# mkdir ./tmpData/$bigServer/$packageVersion/$toPath/$packageVersion/res/UpdatePlist/ccs
# cp -rf $projPath/ccs2proj/cocosstudio/ccs/UiImages ./tmpData/$bigServer/$packageVersion/$toPath/$packageVersion/res/UpdatePlist/ccs/

echo "结束处理文件 check_current_files"
date

