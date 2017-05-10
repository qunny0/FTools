#!/bin/bash

# 统一的入口

DIR="$( cd "$( dirname "$0" )" && pwd )"
cd $DIR

array=(1.0)
for i in ${array[@]}; do
	./upd_enter.sh Tencent cn $i
	# ./upd_enter_for_res.sh Tencent cn $i
	if [ $? -ne 0 ];then 
		echo "生成更新包失败"
		exit 1
	fi
done

# ./addResVerAndCommit.sh Tencent
# if [ $? -ne 0 ];then 
# 	echo "写版本号或提交失败"
# 	exit 1
# fi
