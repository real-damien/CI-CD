#!/ bin / bash
SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""
TEST_FILE=(
    "tests/test1.txt"
    "tests/test2.txt"
)

s21_grep="./s21_grep"
grep="grep"

flags=(
    "i"
    "v"
    "c"
    "l"
    "n"
    "h"
    "s"
    "o"
)

patterns=(
    "main"
    "int"
    "1"
)

flags_e=(
    "-e main -e -rf -e 1"
)

flags_f=(
    "f"
)

printf "\n"
echo "#######################"
echo "MANUAL TEST FOR -e"
echo "#######################"
printf "\n"

for var1 in "${flags_e[@]}"
do
    for var2 in "${TEST_FILE[@]}"
    do
        (( COUNTER++ ))
        TEST1="$var1 $var2"

        $s21_grep $TEST1 > test_result_s21_grep.txt
        $grep $TEST1 > test_result_grep.txt
        DIFF_RES="$(diff -s test_result_s21_grep.txt test_result_grep.txt)"
        if [ "$DIFF_RES" == "Files test_result_s21_grep.txt and test_result_grep.txt are identical" ]
            then
                (( SUCCESS++ ))
                echo "$COUNTER - \033[32mSUCCESS\033[0m $TEST1"
            else
                echo "$TEST1" >> log.txt
                (( FAIL++ ))
                echo "$COUNTER - \033[31mFAIL\033[0m $TEST1"
        fi
        rm test_result_s21_grep.txt test_result_grep.txt
    done
done

printf "\n"
echo "#######################"
echo "MANUAL TEST FOR -f"
echo "#######################"
printf "\n"

for var1 in "${flags_f[@]}"
do
    for var2 in "${grep[@]}"
    do
        (( COUNTER++ ))
        TEST1="$var1 $var2"

        $s21_grep $TEST1 > test_result_s21_grep.txt
        $grep $TEST1 > test_result_grep.txt
        DIFF_RES="$(diff -s test_result_s21_grep.txt test_result_grep.txt)"
        if [ "$DIFF_RES" == "Files test_result_s21_grep.txt and test_result_grep.txt are identical" ]
            then
                (( SUCCESS++ ))
                echo "$COUNTER - \033[32mSUCCESS\033[0m $TEST1"
            else
                echo "$TEST1" >> log.txt
                (( FAIL++ ))
                echo "$COUNTER - \033[31mFAIL\033[0m $TEST1"
        fi
        rm test_result_s21_grep.txt test_result_grep.txt
    done
done



printf "\n"
echo "#######################"
echo "AUTOTESTS"
echo "#######################"
printf "\n"
echo "======================="
echo "0 FLAG - 1 PATTERN - 1 FILE"
echo "======================="
printf "\n"

for var1 in "${patterns[@]}"
do
    for var2 in "${TEST_FILE[@]}"
    do
        (( COUNTER++ ))
        TEST1="$var1 $var2"

        $s21_grep $TEST1 > test_result_s21_grep.txt
        $grep $TEST1 > test_result_grep.txt
        DIFF_RES="$(diff -s test_result_s21_grep.txt test_result_grep.txt)"
        if [ "$DIFF_RES" == "Files test_result_s21_grep.txt and test_result_grep.txt are identical" ]
            then
                (( SUCCESS++ ))
                echo "$COUNTER - \033[32mSUCCESS\033[0m $TEST1"
            else
                echo "$TEST1" >> log.txt
                (( FAIL++ ))
                echo "$COUNTER - \033[31mFAIL\033[0m $TEST1"
        fi
        rm test_result_s21_grep.txt test_result_grep.txt
    done
done

printf "\n"
echo "#######################"
echo "AUTOTESTS"
echo "#######################"
printf "\n"
echo "======================="
echo "1 FLAG - 1 PATTERN - 1 FILE"
echo "======================="
printf "\n"

for var1 in "${flags[@]}"
do
    for var2 in "${patterns[@]}"
    do 
        for var3 in "${TEST_FILE[@]}"
        do
            (( COUNTER++ ))
            TEST1="-$var1 $var2 $var3"

            $s21_grep $TEST1 > test_result_s21_grep.txt
            $grep $TEST1 > test_result_grep.txt
            DIFF_RES="$(diff -s test_result_s21_grep.txt test_result_grep.txt)"
            if [ "$DIFF_RES" == "Files test_result_s21_grep.txt and test_result_grep.txt are identical" ]
                then
                    (( SUCCESS++ ))
                    echo "$COUNTER - \033[32mSUCCESS\033[0m $TEST1"
                else
                    echo "$TEST1" >> log.txt
                    (( FAIL++ ))
                    echo "$COUNTER - \033[31mFAIL\033[0m $TEST1"
            fi
            rm test_result_s21_grep.txt test_result_grep.txt
        done
    done
done

printf "\n"
echo "FAILED: $FAIL"
echo "SUCCESSFUL: $SUCCESS"
echo "ALL: $COUNTER"
printf "\n"

if [ -e log.txt ]; then
    rm log.txt
fi

if [ $FAIL -gt 0 ]; then
    echo "\033[31mTEST FAILED\033[0m"
        exit 1
else
    echo "\033[32mTEST PASSED\033[0m"
fi
##############################