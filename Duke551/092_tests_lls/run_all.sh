#!/bin/bash

vg="valgrind --leak-check=full --log-file=vg.log --error-exitcode=33"

echo "**Testing correct implementation **"
echo "-----------------------------------"
g++ -o test-lls test-lls.cpp /usr/local/ece551/lls/il.o
if [ "$?" != "0" ]
then
    echo "Could not compile test-lls.cpp with il.o" 1>&2
    exit 1
fi
timeout -s 9 10 $vg ./test-lls
if [ "$?" != "0" ]
then
    echo "Your test program falsely failed the correct implementation!" 1>&2
    exit 1
fi
echo ""

for i in /usr/local/ece551/lls/il*.o
do
    test=`basename $i | cut -c3- | cut -f1 -d"."`
    if [ "$test" == "" ]
    then
	continue
    fi
    echo "**Testing broken implementation ${test}**"
    echo "-----------------------------------"
    g++ -o test-lls test-lls.cpp $i
    if [ "$?" != "0" ]
    then
	echo "Could not compile test-lls.cpp with ${i}" 1>&2
	exit 1
    fi
    timeout -s 9 10 $vg ./test-lls
    if [ "$?" == "0" ]
    then
	echo "Your test program did not identify ${i} as broken!" 1>&2
        exit 1
    fi
    echo ""
done

