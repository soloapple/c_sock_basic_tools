#!/bin/bash

for i in {1..100000}
do
	x=$(($i%10000))
	if [ $x -eq 0 ];then
		echo $i
	fi

	task_id=${i}
	logger -t "filesync" -p local4.info "mode=\"10\", type=\"6\", msg=\"Ӧ��:����ģʽ, ����:��������, �����:${task_id}\""
	logger -t "manage" -p local1.info "mode=\"50\",  msg=\"������־:${task_id}\""
done
