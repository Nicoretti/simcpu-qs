#!/bin/sh


./simcpu asm-files/brc.obj
./simcpu asm-files/brn.obj
./simcpu asm-files/brz.obj

./simcpu asm-files/brc_fail.obj
./simcpu asm-files/brc_fail2.obj
./simcpu asm-files/brn_fail.obj
./simcpu asm-files/brz_fail.obj

./simcpu asm-files/kgv.obj

./simcpu blbal
./simcpu
