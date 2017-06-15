#!/bin/bash
#rm -rf cccc
gcc mysql_insert_table.c -L/lib64 -lmysqlclient -o cccc 
#gcc mysql_insert_reckon_time.c -L/lib64 -lmysqlclient -o cccc 
#gcc mysql_query_reckon_time.c -L/lib64 -lmysqlclient -o cccc 
#gcc mysql_query_table.c -L/lib64 -lmysqlclient -o cccc 
#scp cccc 172.24.141.13:/root
#rm -rf cccc
g++ write_syslogng_to_file.cc -lpthread -o write_syslogng_to_file
sz write_syslogng_to_file
sz cccc
