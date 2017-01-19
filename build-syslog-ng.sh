#!/bin/bash

mkdir -p /usr/local/syslog-ng
rm -rf syslog-ng-3.5.6
tar -zxvf syslog-ng_3.5.6.tar.gz 
cp -rf /revive/git/c_sock_basic_tools/include/colorpt.h syslog-ng-3.5.6/lib
cp -rf syslog-ng.h syslog-ng-3.5.6/lib
cd syslog-ng-3.5.6 && ./configure --prefix=/usr/local/hawk/syslog-ng
make
make install
