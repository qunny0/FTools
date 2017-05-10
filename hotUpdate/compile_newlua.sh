#!/bin/bash
DIR="$( cd "$( dirname "$0" )" && pwd )"
bigServer=$1
packageVersion=$2
pathsource="./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile/luascript"
pathout="./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile/Encrypt/"


if [ -d "./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile2" ]; then
	rm -rf ./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile2
fi
mkdir ./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile2

cp -rf ./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile/ ./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile2

echo "替换源文件路径和加密后文件输出路径"
echo $DIR
sed -i '' "s#newfileSourcePath#${pathsource}#g"  $DIR/Main.cpp
sed -i '' "s#newfileOutPath#${pathout}#g"  $DIR/FileEncrypt.cpp
 
g++ -c FileEncrypt.cpp -o FileEncrypt.o

g++ -g FileEncrypt.o Main.cpp -I. -o main

./main

echo "加密结束还原文件参数"
sed -i '' "s#${pathsource}#newfileSourcePath#g"  $DIR/Main.cpp
sed -i '' "s#${pathout}#newfileOutPath#g"  $DIR/FileEncrypt.cpp

if [ -f "./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile/Encrypt/luascript/startGame.lua" ]; then
	cp -rf ./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile/Encrypt/luascript/startGame.lua ./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile/Encrypt/luascript/luascript/startGame.lua
	rm -rf ./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile/Encrypt/luascript/startGame.lua
fi
