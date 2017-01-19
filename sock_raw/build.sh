#!/bin/bash

make clean
make
md5sum net_raw_data_passer
scp net_raw_data_passer 10.0.0.251:/storage
scp net_raw_data_passer 10.0.0.252:/storage
scp grap_raw_link_pkg 10.0.0.251:/storage
scp grap_raw_link_pkg 10.0.0.252:/storage
scp icmp_raw_grap 10.0.0.251:/storage
scp icmp_raw_grap 10.0.0.252:/storage
make clean
