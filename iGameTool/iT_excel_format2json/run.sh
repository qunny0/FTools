#!/bin/bash

DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR

exceldir='/Users/fubei/Documents/git/FTools/games/Levels/configExcel'
ourdir='/Users/fubei/Documents/git/FTools/games/Levels/assets/resources/config'

echo $exceldir '->' $ourdir

node ./run.js $exceldir $ourdir