#!/bin/bash

DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR

exceldir='./../../../config/excelconfig'
ourdir='./../../../config/Stable'

echo $exceldir '->' $ourdir

# node ./iTExcelExport.js $exceldir $ourdir

echo $exceldir '->' $testourdir

testourdir='./../../../config/testing'

node ./iTExcelExport.js $exceldir $testourdir
