#!/bin/bash

echo "Stratified" >> out_ffasp.txt
echo "Stratified" >> out_alv.txt
for file in strat/*
do
	echo "( time ../ffasp $file )" >> out_ffasp.txt 2>&1
	( time ../ffasp $file ) >> out_ffasp.txt 2>&1
	echo "( time ../gringo $file | ../fasp --mode=answer-set)" >> out_alv.txt 2>&1 
	( time ../gringo $file | ../fasp --mode=answer-set) >> out_alv.txt 2>&1
done

echo "Odd" >> out_ffasp.txt
echo "Odd" >> out_alv.txt
for file in odd/*
do
	echo "( time ../ffasp $file )" >> out_ffasp.txt 2>&1
	( time ../ffasp $file ) >> out_ffasp.txt 2>&1
	echo "( time ../gringo $file | ../fasp --mode=answer-set)" >> out_alv.txt 2>&1 
	( time ../gringo $file | ../fasp --mode=answer-set) >> out_alv.txt 2>&1
done

echo "graph-col" >> out_ffasp.txt
echo "graph-col" >> out_alv.txt

for den in $(seq 20 20 100)
do
	echo "Denom=$den" >> out_ffasp.txt
	echo "Denom=$den" >> out_alv.txt
	for file in graph-col/$den/*
	do
		echo "( time ../ffasp $file )" >> out_ffasp.txt 2>&1
		( time ../ffasp $file ) >> out_ffasp.txt 2>&1
		echo "( time ../gringo $file | ../fasp --mode=answer-set)" >> out_alv.txt 2>&1 
		( time ../gringo $file | ../fasp --mode=answer-set) >> out_alv.txt 2>&1
	done
done

echo "ham-path" >> out_ffasp.txt
echo "ham-path" >> out_alv.txt

for den in $(seq 20 20 100)
do
	echo "Denom=$den" >> out_ffasp.txt
	echo "Denom=$den" >> out_alv.txt
	for file in ham-path/$den/*
	do
		echo "( time ../ffasp $file )" >> out_ffasp.txt 2>&1
		( time ../ffasp $file ) >> out_ffasp.txt 2>&1
		echo "( time ../gringo $file | ../fasp --mode=answer-set)" >> out_alv.txt 2>&1 
		( time ../gringo $file | ../fasp --mode=answer-set) >> out_alv.txt 2>&1
	done
done
