#!/bin/bash

DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR

exceldir='../../games/Levels/configExcel'
ourdir='../../games/Levels/assets/resources/config'

echo $exceldir '->' $ourdir

node ./run.js $exceldir $ourdir