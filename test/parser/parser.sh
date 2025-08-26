#!/bin/bash

ESC=$(printf "\033")
END="${ESC}[m"
BRIGHT_RED="${ESC}[91m"
BRIGHT_GREEN="${ESC}[92m"

PARSER="$1"
LOG_DIR="$2"
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
        if [ "$EXPECTED" = "0" ]; then
            $PARSER "${RT_DIR}${RT_FILE}" > "${LOG_DIR}/parser_valid_$(basename "$RT_FILE" .rt).log"
        else
            $PARSER "${RT_DIR}${RT_FILE}"
        fi
        if [ $? -eq "$EXPECTED" ]; then
            printf "%-12s: %s\n" "$RT_FILE" "${BRIGHT_GREEN}SUCCESS${END}"
        else
            printf "%-12s: %s\n" "$RT_FILE" "${BRIGHT_RED}FAILED${END}"
            exit 1
        fi
        NUM=$((NUM + 1))
    done
}

echo "----- valid case -----"
run_parse_test "$VALID_RT_DIR" 0
echo
echo "---- invalid case ----"
run_parse_test "$INVALID_RT_DIR" 1
