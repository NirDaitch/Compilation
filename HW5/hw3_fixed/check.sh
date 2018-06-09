#!/bin/bash

numtests=50

i="1"
while [ $i -le $numtests ]
	do
		./hw3 < tests/t$i.in >& tests/t$i.res
		diff tests/t$i.res tests/t$i.out &> /dev/null
		#diff tests/t$i.res tests/t$i.out 
		if [[ $? != 0 ]] 
			then
				echo "Failed test #"$i"!"
		fi
		i=$[$i+1]
done

