#!/bin/bash

if [[ $# -eq 0 ]] 
	then 
		flag=$("") 
	else 
		flag=$("valgrind") 
fi

# Test cases arr
dead_cases=(
    "3 200 100 100"
    "10 200 100 101"
    "30 100 200 50"
	"100 100 100 100"
	"200 120 60 60"
	"100 101 100 100"
	"123 321 123 3210"
	"10 5 5 5"
	"20 1000 2000 500"
	"50 2000 500 3000"
	"200 60 61 2000"
	"200 61 60 60"
	"1 650 300 300"
)

error_cases=(
	"1000 2147483647 2147483647 2147483648"
	"1000 2147483648 2147483647 2147483647"
	"1000 2147483647 2147483648 2147483647"
	"0 0 0 0"
	"0 0 0 0 0"
	"50 0 100 100 100 100"
	"0 100 100 100 100 100"
	"50 100 0 100 100 100"
	"50 100 100 00 100 100"
	"50 100 100 100 0 100"
	"50 100 100 100 0 0"
	"2147483647 2147483647 2147483647 2147483647"
	"1000 2147483648 2147483648 2147483648 2147483648"
	"0 0 0 0 9"
	"-1 -3 -4 -5"
	"asdf jijioqwer\qwerjf\qwef \asf"
	"\0 \\123 \31"
)

success_cases=(
	"20 401 200 200 50"
	"11 601 200 200 60"
	"1000 2000 100 100 20"
	"1000 1000 100 100 100"
	"200 200 60 60 50"
	"60 600 200 200 10"
)

# Execute the program with each test case
for dead_case in "${dead_cases[@]}"; do
    echo "Running test case: $dead_case"
    echo "---------------------"
	output=$($(flag) ./philo_1 $dead_case)
	echo "$output" | tail -n 6
    echo "---------------------"
    echo ""
done

for error_case in "${error_cases[@]}"; do
    echo "Running test case: $error_case"
    echo "---------------------"
	$(flag) ./philo_1 $error_case
    echo "---------------------"
    echo ""
done

for success_case in "${success_cases[@]}"; do
	echo "Running test case: $success_case"
	echo "--------------------"
	output=$(./philo_1 $success_case)
	eat=$(echo "$output" | grep eat | wc -l)
	sleep=$(echo "$output" | grep sleep | wc -l)
	think=$(echo "$output" | grep think | wc -l)
	dead=$(echo "$output" | grep dead | wc -l)
	echo "eat count = $eat"
	echo "sleep count = $sleep"
	echo "think count = $think"
	echo "dead = $dead"
	echo "--------------------"
	echo ""
done
