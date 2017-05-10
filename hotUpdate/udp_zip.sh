#!/bin/bash
DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR
version_str=$1
path='/Users/wxg/Documents/CocosProjects/shipwar_trunk/test/'
project='/Users/wxg/Documents/CocosProjects/shipwar_trunk/LandKing'

if [[ ! -d $project ]];then
            mkdir $project
	cd $project
	svn checkout http://svn.raysns.com/repos/shipwar/client/trunk/LandKing
	cd $DIR
fi
rm -rf $path'target'
if [[ ! -f $path'target' ]]; then
    touch $path'target'
fi
cd $project
svn cleanup
#svn update

OLD_IFS="$IFS"
IFS=","
arr=($version_str)
IFS="$OLD_IFS"
for version in ${arr[@]}
do
	svn log -r$version -v|grep '/client/trunk/LandKing'|cut -c 6->>$path'target'
done
for line in `cat $path'target'`
do
    dis=$path${line/\/client\/trunk\/LandKing/}
    src=$project${line/\/client\/trunk\/LandKing/}
    if [[ -d $src ]]; then
        mkdir -p $dis
    else
        f_dis=${dis%/*}
        if [[ ! -d $f_dis ]]; then
            mkdir -p $f_dis
        fi
        cp -rf $src $f_dis
    fi
done
echo $DIR
cd $DIR
zip -ru updpart.zip test/
#svn commit -m "========"

