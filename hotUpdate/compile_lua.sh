#!/bin/bash

# 编译
DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR
# ./compile_lua.sh 大服名 安装包版本

projPath="../TankWar2/LandKing"
bigServer=$1
packageVersion=$2

# luascript
if [ -d "./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile2" ]; then
	rm -rf ./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile2
fi
mkdir ./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile2

cp -rf ./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile/ ./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile2

# if [ -d "./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile/$packageVersion/src" ]; then
# 	$projPath/../quick/quick/bin/compile_scripts.sh -i ./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile/$packageVersion/src -o ./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile/$packageVersion/src -m files -e xxtea_chunk -ek jhg734uff85v -es XT
# fi
