#!/bin/bash

# 将测试包还原到线上

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

cp -rf ../publish/$bigServer/upd/cdn.php ../publish/$bigServer/updtest/cdn.php

cd ../publish/$bigServer/updtest
svn commit -m "测试包放回线上"
cd $DIR