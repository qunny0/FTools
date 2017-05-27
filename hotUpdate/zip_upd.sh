#!/bin/bash

# 将willZipResAndSrcFile压缩为可供前端下载的zip包
DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR

# 用法 ./zip_upd.sh 大服名 安装包版本 资源版本

bigServer=$1
packageVersion=$2
updPath="$( cd ../updPackageFile/$bigServer && pwd )"
resVersion=$3
oldResVersion=$[$resVersion-1]

cd ./tmpData/$bigServer/$packageVersion/willZipResAndSrcFile/Encrypt/luascript/Resources/

if [[ ! -d "$updPath/zipfiles/updtest/$packageVersion/$resVersion/full" ]]; then
	mkdir "$updPath/zipfiles/updtest/$packageVersion/$resVersion"
	mkdir "$updPath/zipfiles/updtest/$packageVersion/$resVersion/full"
fi
if [[ ! -d "$updPath/zipfiles/updtest/$packageVersion/$resVersion/part" ]]; then
	mkdir "$updPath/zipfiles/updtest/$packageVersion/$resVersion"
	mkdir "$updPath/zipfiles/updtest/$packageVersion/$resVersion/part"
fi
#  全包
cp -f $updPath/zipfiles/upd/$packageVersion/$oldResVersion/full/luascript.zip $updPath/zipfiles/updtest/$packageVersion/$resVersion/full/luascript.zip
zip -ru $updPath/zipfiles/updtest/$packageVersion/$resVersion/full/luascript.zip ./* -x *.DS_Store*

#  分包
rm -rf $updPath/zipfiles/updtest/$packageVersion/$resVersion/part/luascript.zip
zip -r $updPath/zipfiles/updtest/$packageVersion/$resVersion/part/luascript.zip ./* -x *.DS_Store*
