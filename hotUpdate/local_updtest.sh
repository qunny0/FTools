#!/bin/bash

# 将测试包放在本地

DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR

bigServer=$1

if [[ ! -d "../publish" ]]; then
	mkdir "../publish"
fi
if [[ ! -d "../publish/$bigServer" ]]; then
	cd ../publish/
	svn checkout http://publish.rayjoy.com/repos/landking/publish/$bigServer/tankwarclient $bigServer	
	cd $DIR
fi
cd ../publish/$bigServer
svn update
cd $DIR

sed -i '' 's/return .*/return "http:\/\/'$(ifconfig | grep "inet 192" | awk '{print $2}')':8080\/";/g' ../publish/$bigServer/updtest/cdn.php 
rsync -avz --delete ../publish/$bigServer/zipfiles/updtest/ /Users/zhaozhantao/me/apache-tomcat-8.0.23/webapps/ROOT/updtest/

cd ../publish/$bigServer/updtest
svn commit -m "测试包放本地"
cd $DIR
