#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="test.txt"

for var in -v -b -e -n -s -t
do
          TEST1="$var $TEST_FILE"
          echo "$TEST1"
          ./../cat/s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
              echo "SUCCESSED"
            else
              (( COUNTER_FAIL++ ))
              echo "FAILED"
          fi
          rm s21_cat.txt cat.txt
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"