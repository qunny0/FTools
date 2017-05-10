#!/bin/bash

# 将willZipResAndSrcFile压缩为可供前端下载的zip包
DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR

# 用法 ./zip_upd.sh 大服名 安装包版本 资源版本

bigServer=$1
packageVersion=$2
updPath="$( cd ../sdk_pub/$bigServer && pwd )"
resVersion=$3
oldResVersion=$[$resVersion-1]

cd ./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile/Encrypt/luascript

if [[ ! -d "$updPath/clientcdn/updtest/$packageVersion/$resVersion/full" ]]; then
	mkdir "$updPath/clientcdn/updtest/$packageVersion/$resVersion"
	mkdir "$updPath/clientcdn/updtest/$packageVersion/$resVersion/full"
fi
if [[ ! -d "$updPath/clientcdn/updtest/$packageVersion/$resVersion/part" ]]; then
	mkdir "$updPath/clientcdn/updtest/$packageVersion/$resVersion"
	mkdir "$updPath/clientcdn/updtest/$packageVersion/$resVersion/part"
fi
#  全包
cp -f $updPath/clientcdn/upd/$packageVersion/$oldResVersion/full/luascript.zip $updPath/clientcdn/updtest/$packageVersion/$resVersion/full/luascript.zip
zip -ru $updPath/clientcdn/updtest/$packageVersion/$resVersion/full/luascript.zip ./* -x *.DS_Store*

#  分包
rm -rf $updPath/clientcdn/updtest/$packageVersion/$resVersion/part/luascript.zip
zip -r $updPath/clientcdn/updtest/$packageVersion/$resVersion/part/luascript.zip ./* -x *.DS_Store*
