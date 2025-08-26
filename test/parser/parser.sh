#!/bin/bash

ESC=$(printf "\033")
END="${ESC}[m"
BRIGHT_RED="${ESC}[91m"
BRIGHT_GREEN="${ESC}[92m"

PARSER="$1"
VALID_RT_DIR="./scene_file/valid/"
INVALID_RT_DIR="./scene_file/invalid/"

run_parse_test () {
    NUM=1
    RT_DIR="$1"
    EXPECTED="$2"
    while true
    do
        RT_FILE="example${NUM}.rt"
        if [ ! -f "${RT_DIR}${RT_FILE}" ]; then
            break
        fi
        $PARSER "${RT_DIR}${RT_FILE}"
        if [ $? -eq "$EXPECTED" ]; then
            printf "%-30s: %s\n" "$RT_FILE" "${BRIGHT_GREEN}SUCCESS${END}"
        else
            printf "%-30s: %s\n" "$RT_FILE" "${BRIGHT_RED}FAILED${END}"
        fi
        NUM=$((NUM + 1))
    done
}

run_parse_test "$VALID_RT_DIR" 0
run_parse_test "$INVALID_RT_DIR" 1
