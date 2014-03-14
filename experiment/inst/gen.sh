#!/bin/bash
for den in $(seq 120 20 200)
do

#	let suf=125
#	for size in $(seq 10 10 60)
#	do
#		../ffasp --rp=$den ../GraphColouring/$size-graph_colouring-$suf-0.asp  > graph-col/$den/col-$size-$den.lp
#		cat ../GraphColouring/graph-colouring.lp >> graph-col/$den/col-$size-$den.lp
#		let suf=suf+5
#	done
	for nmr in $(seq 11 1 20)
	do
		../ffasp --rp=$den ../HamPath/$nmr-HamPath > ham-path/$den/ham-$nmr-$den.lp
		cat ../HamPath/ham-path.lp >> ham-path/$den/ham-$nmr-$den.lp
	done
done


