#!/bin/bash

SEARCH_PATH="/storage /usr/local/hawk/ /etc"

SRC1="127.0.16.1"
DST1="192.168.160.1"

SRC2="127.0.16.2"
DST2="192.168.160.2"

SRC3="20.20.20.100"
DST3="172.24.128.51"

for j in ${SEARCH_PATH}
do
	conf_file=`find ${j} -maxdepth 4 -type f|xargs grep ${SRC1} -l`
	for i in ${conf_file}
	do
		echo ${i}
		sed -i "s/${SRC1}/${DST1}/g" ${i}
	done
done

for j in ${SEARCH_PATH}
do
	conf_file=`find ${j} -maxdepth 4 -type f|xargs grep ${SRC2} -l`
	for i in ${conf_file}
	do
		echo ${i}
		sed -i "s/${SRC2}/${DST2}/g" ${i}
	done
done

for j in ${SEARCH_PATH}
do
	conf_file=`find ${j} -maxdepth 4 -type f|xargs grep ${SRC3} -l`
	for i in ${conf_file}
	do
		echo ${i}
		sed -i "s/${SRC3}/${DST3}/g" ${i}
	done
done
