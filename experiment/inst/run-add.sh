#!/bin/bash


echo "ham-path" >> out_ffasp.txt
echo "ham-path" >> out_alv.txt

for den in $(seq 120 20 160)
do
	for file in ham-path/$den/*
	do
		echo "( time  ../ffasp $file )" >> out_ffasp.txt 2>&1
		( time ../ffasp $file ) >> out_ffasp.txt 2>&1
		echo "( time timeout -t 602 ../gringo $file | ../fasp --mode=answer-set)" >> out_alv.txt 2>&1 
		( time ../gringo $file | ../fasp --mode=answer-set) >> out_alv.txt 2>&1
	done
done
