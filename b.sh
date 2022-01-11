#!/bin/bash
target=cleaner

rm ${target}
gcc -o ${target} main.c && ./${target} ~/projects/_files/
