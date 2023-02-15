#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
WHITE='\033[0;37m'
input_dir="test/TestFiles"

output_dir="$input_dir/output"

executable="miniRT"

for input_file in "$input_dir"/*; do
    # get name without ending
    base_name="$(basename "$input_file")"

    # Create output filename
    output_file="$output_dir/${base_name%.*}_out"
    # Create cmp filename
    cmp_file="$output_dir/${base_name%.*}_cmp"
    # create valgrind log file
    log_file="test/valgrind/${base_name%.*}_val"

    ./$executable "$input_file" > "$output_file"

    diff "$output_file" "$cmp_file"
    if [ $? -eq 0 ]; then
      echo -e $base_name ": ${GREEN}OK${WHITE}\n"
    else
      echo -e "${RED}Error: ${WHITE}" $base_name
      break
    fi
    rm -f $output_file
    #rm -f $log_file
    #touch $log_file
    
    #valgrind --leak-check=full --log-file=$log_file  ./$executable $input_file 

    # Check the output against an ignore file to see if there are actual leaks
    #rm -f test/valgrind/cmp
    #touch test/valgrind/cmp
    #uniq $log_file test/valgrind/val_cmp > test/valgrind/cmp
    #if [ $(wc -l < test/valgrind/cmp) -gt 0 ]; then
        #echo -e "${RED} leak: ${WHITE}" $base_name
    #fi
done

