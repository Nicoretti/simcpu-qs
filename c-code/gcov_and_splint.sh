#!/bin/sh
# runs all tests to get 100% instruction coverage
./create_obj_files.sh

./simcpu ../simcpu-obj-files/brc.obj >> test.log
./simcpu ../simcpu-obj-files/brn.obj >> test.log
./simcpu ../simcpu-obj-files/sbrz.obj >> test.log

./simcpu ../simcpu-obj-files/brc_fail.obj >> test.log
./simcpu ../simcpu-obj-files/brc_fail2.obj >> test.log
./simcpu ../simcpu-obj-files/brn_fail.obj >> test.log
./simcpu ../simcpu-obj-files/brz_fail.obj >> test.log

./simcpu ../simcpu-obj-files/kgv.obj >> test.log

./simcpu blbal >> test.log
./simcpu >> test.log

gcov main
gcov simcpu_types

splint main.c
splint simcpu_types.c
