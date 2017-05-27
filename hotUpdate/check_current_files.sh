#!/bin/bash

# 从前端工程检出当前文件
DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR

# 用法 ./check_current_files.sh 大服名 语言 安装包版本 检出到的目录(只有名称，没有路径) 工程源（1或2）

projPath="../TankWar$5"
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
mkdir ./tmpData/$bigServer/$packageVersion/$toPath/luascript

echo "开始处理文件 check_current_files"
date

rsync -avz --delete --exclude ".svn" $projPath/Resources 		./tmpData/$bigServer/$packageVersion/$toPath/luascript/
rsync -avz --delete --exclude ".svn" $projPath/ResEmpireWar ./tmpData/$bigServer/$packageVersion/$toPath/luascript/

# if [ -d "./$language" ]; then
# 	echo "error: ./$language 已存在"
# 	exit 1
# fi
# rm -rf ./tmpData/$bigServer/$packageVersion/$toPath/luascript/Resources/de

echo "结束处理文件 check_current_files"
date
