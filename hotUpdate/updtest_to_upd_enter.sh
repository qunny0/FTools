#!/bin/bash

# 测试包转正式包
# ./updtest_to_upd.sh 大服名

DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR

bigServer=$1
updPath="../updPackageFile/$bigServer"

# grep -q "192" $updPath/updtest/cdn.php  && echo "测试环境的更新包仍在本地" && exit 1

# cp -rf $updPath/updtest/ $updPath/upd/
# cp -rf $updPath/zipfiles/updtest/ $updPath/zipfiles/upd/
rsync -avz --delete $updPath/svnfiles/updtest/ $updPath/svnfiles/upd/
rsync -avz --delete $updPath/zipfiles/updtest/ $updPath/zipfiles/upd/

cd $updPath/svnfiles/upd
svn add * --force
svn commit -m "测试上传"
cd ../../zipfiles/upd
svn stat | grep \\! | awk '{print $2}' | xargs svn remove
svn add * --force
svn commit -m "测试上传"
