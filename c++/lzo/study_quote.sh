#!/bin/bash

getfilename=`realpath study_double_quote.sh`
ls -l "${getfilename}"

echo '============================'

getfilename=`realpath *.sh`
ls | while IFS='' read -r line
do
	ls -l "${line}"
done
