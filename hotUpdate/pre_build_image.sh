#!/bin/bash

DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR

echo $DIR

# rm -rf $DIR/NewResPlist/*
# echo "svn update ResEmpireWar >>>"
# svn update Tank/ResEmpireWar

# buildType=1
# targetPath=$DIR/Tank/ResEmpireWar
# buildPath=$DIR/Tank/ResEmpireWar
# if ! [[ $1 == "" ]]; then
#   buildPath=$DIR/Tank/ResEmpireWar/$1
#   buildType=2
# fi

echo ">>>>>>>>buildPath:$buildPath;buildType:$buildType"

function contains() {
    local n=$#
    local value=${!n}
    for ((i=1;i < $#;i++)) {
        if [ "${!i}" == "${value}" ]; then
            echo "y"
            return 0
        fi
    }
    echo "n"
    return 1
}

changeFolderList=()

function loadImagePaths(){
  for file in `ls $1`
  do
      changeFolderList[${#changeFolderList[@]}+1]=$file
  done
}

if [[ $buildType == 2 ]]; then
    changeFolderList[${#changeFolderList[@]}+1]=$1
else
    loadImagePaths $buildPath
fi

# echo "remove all file of NewResPlist"
# rm -rf $DIR/NewResPlist/*

TextureTypePng=(
)

TextureFormat8888=(
  homeBuilding
  newUnCompress
  clickBuilding
)

for folderPath in ${changeFolderList[@]}; do
  echo "合图：$folderPath"
  fileName=$folderPath.pvr.ccz
  if [[ $(contains "${TextureTypePng[@]}" $folderPath) == "y" ]]; then
    fileName=$folderPath.png
  fi
  if [[ $(contains "${TextureFormat8888[@]}" $folderPath) == "y" ]]; then
    TexturePacker $targetPath/$folderPath --data $DIR/NewResPlist/$folderPath.plist --format cocos2d --sheet $DIR/NewResPlist/$fileName --allow-free-size --shape-padding 2 --border-padding 0 --opt RGBA8888 --disable-rotation --dither-fs-alpha
  else
    TexturePacker $targetPath/$folderPath --data $DIR/NewResPlist/$folderPath.plist --format cocos2d --sheet $DIR/NewResPlist/$fileName --allow-free-size --shape-padding 2 --border-padding 0 --opt RGBA4444 --disable-rotation --dither-fs-alpha
  fi
  sed -i '' "/smartupdate/d"  $DIR/NewResPlist/$folderPath.plist
  sed -i '' "/TexturePacker:SmartUpdate/d"  $DIR/NewResPlist/$folderPath.plist
done

# sh copy.sh Tank/Resources
