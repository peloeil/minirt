#!/bin/bash

ESC=$(printf "\033")
END="${ESC}[m"
BRIGHT_RED="${ESC}[91m"
BRIGHT_GREEN="${ESC}[92m"

PARSER=$1
VALID_PATH="./scene_file/valid/"
INVALID_PATH="./scene_file/invalid/"

run_parse_test () {
    NUM=1
    PATH=$1
    EXPECTED=$2
    while true
    do
        RT_FILE="example${NUM}.rt"
        if [ ! -f "${PATH}${RT_FILE}" ]; then
            break
        fi
        if $PARSER "${PATH}${RT_FILE}"; then
            printf "%-30s: %s\n" $RT_FILE "${BRIGHT_GREEN}SUCCESS${END}"
        else
            printf "%-30s: %s\n" $RT_FILE "${BRIGHT_RED}FAILED${END}"
        fi
        NUM=$((NUM + 1))
    done
}

run_parse_test $VALID_PATH 0
run_parse_test $INVALID_PATH 1
