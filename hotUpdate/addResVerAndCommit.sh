#!/bin/bash

# 提升版本号，并且提交 
# ./addResVerAndCommit.sh 大服名
DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR

bigServer=$1 
updPath="$DIR/../updPackageFile/$bigServer"

resVersion=$[$( cat $updPath/svnfiles/upd/commonVersion.php | grep "return" |awk '{print $NF}'|awk -F';' '{print $1}' )+1]
echo -e "<?php\n	function getCommonVersion()\n	{\n		return $resVersion;\n	}\n?>" > $updPath/svnfiles/updtest/commonVersion.php
echo "资源版本$resVersion"
for i in `ls $updPath/zipfiles/updtest`; do
	cd $updPath/zipfiles/updtest/$i
	ls | grep -v "$resVersion" | xargs rm -rf
done

#提交
cd $updPath/svnfiles/updtest
svn add * --force
svn commit -m "测试提交2"
cd $updPath/zipfiles/updtest
svn stat | grep \\! | awk '{print $2}' | xargs svn remove
svn add * --force
svn commit -m "测试提交2"
