#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
WHITE='\033[0;37m'
input_dir="test/TestFiles"

output_dir="$input_dir/output"

for input_file in "$input_dir"/*; do
    # get name without ending
    base_name="$(basename "$input_file")"

    # Create output filename
    output_file="$output_dir/${base_name%.*}_out"
    # Create cmp filename
    cmp_file="$output_dir/${base_name%.*}_cmp"

    ./miniRT "$input_file" > "$output_file"

    diff "$output_file" "$cmp_file"
    if [ $? -eq 0 ]; then
      echo -e $base_name ": ${GREEN}OK${WHITE}\n"
    else
      echo -e "${RED}Error: ${WHITE}" $base_name
    fi
done

