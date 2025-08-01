#!/bin/bash

##################################################
# Global Variables                               #
##################################################

CUBOID_M_DIR="$(dirname "$(realpath "$0")")"

CUBOID_E_PATH="${CUBOID_M_DIR}/edit/cuboid_match"
CUBOID_S_PATH="${CUBOID_M_DIR}/source/cuboid"

##################################################
# Functions                                      #
##################################################

function test_xyz()
{
    local X="$1"
    local Y="$2"
    local Z="$3"

    echo "Testing X: ${X} Y: ${Y} Z: ${Z}"

    local CUBOID_E_OUT="$($CUBOID_E_PATH "$X" "$Y" "$Z")"
    local CUBOID_S_OUT="$($CUBOID_S_PATH "$X" "$Y" "$Z")"

    if [[ "$CUBOID_E_OUT" != "$CUBOID_S_OUT" ]]; then
        echo "Found difference for X: ${X} Y: ${Y} Z: ${Z}"

        echo -e "Edits:\n${CUBOID_E_OUT}"
        echo -e "Source:\n${CUBOID_S_OUT}"

        return 1
    fi

    return 0
}

function run_xyz()
{
    local START="$1"
    local STOP="$2"

    local X_ARR=($(seq "$START" "$STOP"))
    local Y_ARR=($(seq "$START" "$STOP"))
    local Z_ARR=($(seq "$START" "$STOP"))

    declare i; declare j; declare k

    for ((i = 0; i < "${#X_ARR[@]}"; i++)); do
        for ((j = 0; j < "${#Y_ARR[@]}"; j++)); do
            for ((k = 0; k < "${#Z_ARR[@]}"; k++)); do
                test_xyz "${X_ARR[$i]}" "${Y_ARR[$j]}" "${Z_ARR[$k]}" || return 1
            done
        done
    done

    return 0
}

##################################################
# Mainline                                       #
##################################################

[[ -f "$CUBOID_E_PATH" ]] || { echo "File '${CUBOID_E_PATH}' not found."; exit 1; }
[[ -f "$CUBOID_S_PATH" ]] || { echo "File '${CUBOID_S_PATH}' not found."; exit 1; }

run_xyz "-1" "11" || { echo "Test FAILED!"; exit 1; }

echo "Test PASSED!"

exit 0

