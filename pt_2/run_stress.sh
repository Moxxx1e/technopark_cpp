#!/bin/bash

list_of_files=list_of_stress_files.txt

IFS=$'\n'

for file in stress_test_files/*
do
echo "shared $file"; ./pt_2 $file;
done

