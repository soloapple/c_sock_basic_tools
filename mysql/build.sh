#!/bin/bash
rm -rf cccc
gcc mysql_insert_table.c -L/lib64 -lmysqlclient -o cccc 
scp cccc 172.24.141.28:/root
rm -rf cccc
