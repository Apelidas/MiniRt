#!/bin/bash

dir="TestFiles"

for file in $dir/*
do
	../minirt $file > ($file + "_out")
	if ! diff ($file + "_cmp")
	then
		echo $file
		break
	else
		echo "ok "
	fi
done