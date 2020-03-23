#!/bin/bash

list_of_files=list_of_stress_files.txt

IFS=$'\n'

for file in $(cat $list_of_files)
do
echo "shared $file"; ./pt_2_sh $file;
echo "static $file"; ./pt_2_st $file
done

