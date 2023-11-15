#!/bin/bash

EXE=${1:-'none'}

if [ "${EXE}" = "app" ]; then
    echo "### Solve Santa-Challenge ###"
    ./build/source/santa-challenge
elif [ "${EXE}" = "test" ]; then
    echo "### Run tests for application ###"
    ./build/unittests/santaChallengeTest
else
    echo "No executable for '${EXE}' found"
fi