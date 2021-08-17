#!/usr/bin/env bash

CURRENT_DIR=`pwd`
OLD_GO_PATH="$GOPATH"  #例如: /usr/local/go
OLD_GO_BIN="$GOBIN"    #例如: /usr/local/go/bin

export GOPATH="$CURRENT_DIR" 
export GOBIN="$CURRENT_DIR/bin"

#指定并整理当前的源码路径
gofmt -w src

go install test_hello

export GOPATH="$OLD_GO_PATH"
export GOBIN="$OLD_GO_BIN"


#注：bashrc 对系统所有用户有效，profile 对当前用户有效。
#有三个变量 GOPATH、PATH、GOROOT：
#GOROOT 就是 go 的安装路径；
#GOPATH 就是go的工作目录；
#PATH是go安装路径下的bin目录。
export GOROOT="/usr/local/go"
export GOPATH="/go"
export PATH=$PATH:/usr/local/go/bin
