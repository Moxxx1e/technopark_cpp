#!/bin/bash
cd  cmake-build-debug

list_of_files=list_of_files.txt

IFS=$'\n'

for file in $(cat ../list_of_stress_files.txt)
do
echo "shared $file"; ./pt_2_sh $file;
echo "static $file"; ./pt_2_st $file
done

