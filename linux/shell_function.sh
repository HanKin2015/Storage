#!/bin/bash

function func1()
{
    echo 'I am function 1'
    return
}
func2()
{
    echo 'I am function 2'
    return
}

echo 'start'

ret=func1
echo $ret

func2
echo 'result = $?'

echo 'end'
