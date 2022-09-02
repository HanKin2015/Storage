#!/usr/bin/awk -f

{if($3 >=min && $3<=max)print $1,$3}