#!/bin/bash

#
# this is for logtest. it will send every kind of log test. 
# it only has msg at first. but later, all msg will be fill.
#

#
#  local0 system
#  local1 manage
#  local2 sysrun
#  local3 business
#  local4 alarm
#

#
#  1=tab_system
#  10=tab_filesync
#  11=tab_dbsync
#  12=tab_http
#  13=tab_ftp
#  14=tab_db_visit
#  15=tab_mail
#  16=tab_socks
#  17=tab_tcp
#  18=tab_udp
#  19=tab_ha
#  20=tab_ids
#  21=tab_ssl_channel
#  22=tab_opc
#  50=tab_manage 
#

for i in {1..2}
do
	x=$(($i%10000))
	if [ $x -eq 0 ];then
		echo "Now has insert branch num:$i"
	fi
	task_id=${i}

	# tab_system
	logger -t "system" -p local0.info "mode=\"1\", msg=\"msg system, task num:${task_id}\""

	# tab_manage
	logger -t "manage" -p local1.info "mode=\"50\", msg=\"msg manage, task num:${task_id}\""

	# tab_sysrun
	logger -t "sysrun" -p local2.info "mode=\"12\", msg=\"msg sysrun, task num:${task_id}\""

	# tab_alarm
	logger -t "alarm" -p local4.info "mode=\"1\", type=\"3\", msg=\"msg alarm, task num:${task_id}\""

	# 
	# next is all business log.
	#

	# tab_filesync
	logger -t "filesync" -p local3.warning "mode=\"10\", msg=\"msg filesync, task num:${task_id}\""
	# tab_dbsync
	logger -t "dbsync" -p local3.warning "mode=\"11\", msg=\"msg dbsync, task num:${task_id}\""
	# tab_http
	logger -t "http" -p local3.warning "mode=\"12\", msg=\"msg http, task num:${task_id}\""
	# tab_ftp
	logger -t "ftp" -p local3.warning "mode=\"13\", msg=\"msg ftp, task num:${task_id}\""
	# tab_db_visit
	logger -t "db visit" -p local3.warning "mode=\"14\", msg=\"msg db visit, task num:${task_id}\""
	# tab_mail
	logger -t "mail" -p local3.warning "mode=\"15\", msg=\"msg mail, task num:${task_id}\""
	# tab_sock
	logger -t "sock" -p local3.warning "mode=\"16\", msg=\"msg sock, task num:${task_id}\""
	# tab_tcp
	logger -t "tcp" -p local3.warning "mode=\"17\", msg=\"msg tcp, task num:${task_id}\""
	# tab_udp
	logger -t "udp" -p local3.warning "mode=\"18\", msg=\"msg udp, task num:${task_id}\""
	# tab_ha
	logger -t "ha" -p local3.warning "mode=\"19\", msg=\"msg ha, task num:${task_id}\""
	# tab_ids
	logger -t "ids" -p local3.warning "mode=\"20\", msg=\"msg ids, task num:${task_id}\""
	# tab_ssl_channel
	logger -t "ssl" -p local3.warning "mode=\"21\", msg=\"msg ssl, task num:${task_id}\""
	# tab_opc
	logger -t "opc" -p local3.warning "mode=\"22\", msg=\"msg opc, task num:${task_id}\""
done
