#!/bin/bash

for i in {1..100000}
do
	task_id=${i}
	logger -t "filesync" -p local4.info "mode=\"10\", type=\"6\", msg=\"Ӧ��:����ģʽ, ����:��������, �����:${task_id}\""
	logger -t "manage" -p local1.info "mode=\"50\",  msg=\"������־\""
done
