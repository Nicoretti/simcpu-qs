#!/bin/sh

#TODO
#Variables, Consoleinput, check for build if simcpu doesn't exist
if  [ $# -gt 1 ]; then
  echo "Too many arguments. Only one inputfile is allowed!"
	exit 1;
elif [ $# -lt 1 ]; then
	echo "Too few arguments! Only one inputfile is allowed!"
	exit 1;
fi

#Variables
sim=inputToSimulate.txt
executable=simcpu

cd ./python
./assembler.py -i ../$1 -o ../c-code/$sim

cd ../c-code
if [ ! -x $executable ]; then
	echo "$executable does not exist and will be build!"
	make clean > /dev/zero 2> /dev/zero
	make all > /dev/zero 2> /dev/zero
fi
./$executable $sim
#rm $sim
