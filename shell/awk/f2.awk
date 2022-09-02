#!/usr/bin/awk -f

# this is a awk script
{if($3>=1000) print $1,$3}