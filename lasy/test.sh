#!/bin/bash
if (($# != 2)); then
    echo "Wrong usage! Use: ./test.sh ./<program> <directory>"
    exit 1
fi

VALGRIND="valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --quiet"
if [ -x ./$1 ]; then
   PROGRAM=./$1
else
   PROGRAM=$1
fi
DIRECTORY=$2

OUTPUT_PASSED_COUNT=0
TESTS_AMOUNT=0

for i in $DIRECTORY/*.in ; do
    echo -n "Testing ${i#*$DIRECTORY/}... "
    
    $PROGRAM <$i 2>current.err >current.out
    EXIT_CODE=$?
    
    if (($EXIT_CODE == 0)); then 
        echo -n "CORRECT EXIT CODE,  "
    else 
        echo -n "EXIT CODE $EXIT_CODE,  "
    fi

    #Output
    if cmp -s ${i%in}out current.out; then
        if cmp -s ${i%in}err current.err; then
            echo -n "OUTPUT CORRECT,  "
            ((OUTPUT_PASSED_COUNT++))
        else
            echo -n "OUTPUT WRONG,  "
        fi
    else
        echo -n "OUTPUT WRONG,  "
    fi
    
    #Memory
    $VALGRIND $PROGRAM <$i &>/dev/null
    
    if (($EXIT_CODE == 15)); then
        echo "DETECTED MEMORY LEAKS"
    else
        echo "NO MEMORY LEAKS"
    fi
    ((TESTS_AMOUNT++))
done

#Summary
echo "IN $OUTPUT_PASSED_COUNT/$TESTS_AMOUNT OUTPUT OK"

#Cleaning
rm -f current.err current.out

