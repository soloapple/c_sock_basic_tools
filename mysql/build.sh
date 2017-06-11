#!/bin/bash
rm -rf cccc
#gcc mysql_insert_table.c -L/lib64 -lmysqlclient -o cccc 
gcc mysql_insert_reckon_time.c -L/lib64 -lmysqlclient -o cccc 
#gcc mysql_query_table.c -L/lib64 -lmysqlclient -o cccc 
#scp cccc 172.24.141.27:/root
#rm -rf cccc
