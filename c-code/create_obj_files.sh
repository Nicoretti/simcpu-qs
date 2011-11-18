#!/bin/sh
# ATTENTION: Do not call this script directly
# generates obj-files 

../python/assembler.py -i ../asm-files/brc.asm -o  ../simcpu-obj-files/brc.obj
../python/assembler.py -i ../asm-files/brn.asm -o  ../simcpu-obj-files/brn.obj
../python/assembler.py -i ../asm-files/brz.asm -o  ../simcpu-obj-files/brz.obj

../python/assembler.py -i ../asm-files/brc_fail.asm -o  ../simcpu-obj-files/brc_fail.obj
../python/assembler.py -i ../asm-files/brc_fail2.asm -o  ../simcpu-obj-files/brc_fail2.obj
../python/assembler.py -i ../asm-files/brn_fail.asm -o  ../simcpu-obj-files/brn_fail.obj
../python/assembler.py -i ../asm-files/brz_fail.asm -o  ../simcpu-obj-files/brz_fail.obj

../python/assembler.py -i ../asm-files/kgv.asm -o  ..//simcpu-obj-files/kgv.obj

