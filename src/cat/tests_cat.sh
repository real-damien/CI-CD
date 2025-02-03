#!/ bin / bash
SUCCESS=0
FAIL=0
COUNTER=0
TEST_FILE=(
    "tests/test1.txt"
    "tests/test2.txt"
    "tests/test3.txt"
    "tests/test4.txt"
)

s21_cat="./s21_cat"
cat="cat"

flags=(
    "-b"
    "-e"
    "-n"
    "-s"
    "-t"
    "-v"
)

printf "\n"
echo "-----------------------"
echo "TESTS"
echo "-----------------------"
printf "\n"
echo "======================="
echo "1 FLAG - 1 FILE"
echo "======================="
printf "\n"

for v1 in "${flags[@]}"
do
    for v2 in "${TEST_FILE[@]}"
    do
        (( COUNTER++ ))
        TEST1="$v1 $v2"
        
        $s21_cat $TEST1 > s21_cat_res.txt
        $cat $TEST1 > cat_res.txt
        DIFF_RES="$(diff -s s21_cat_res.txt cat_res.txt)"
        if [ "$DIFF_RES" == "Files s21_cat_res.txt and cat_res.txt are identical" ]
            then
                (( SUCCESS++ ))
                echo "$COUNTER - \033[32mSUCCESS\033[0m $TEST1"
            else
                echo "$TEST1" >> log.txt
                (( FAIL++ ))
                echo "$COUNTER - \033[31mFAIL\033[0m $TEST1"
        fi
        rm s21_cat_res.txt cat_res.txt
        
    done
done

##############################

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