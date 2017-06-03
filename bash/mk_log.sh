#!/bin/bash

for i in {1..100000}
do
	x=$(($i%10000))
	if [ $x -eq 0 ];then
		echo $i
	fi

	task_id=${i}
	logger -t "filesync" -p local4.info "mode=\"10\", type=\"6\", msg=\"应用:内置模式, 操作:新增任务, 任务号:${task_id}\""
	logger -t "manage" -p local1.info "mode=\"50\",  msg=\"管理日志:${task_id}\""
done
