#!/usr/bin/env bash

CURRENT_DIR=`pwd`
OLD_GO_PATH="$GOPATH"  #����: /usr/local/go
OLD_GO_BIN="$GOBIN"    #����: /usr/local/go/bin

export GOPATH="$CURRENT_DIR" 
export GOBIN="$CURRENT_DIR/bin"

#ָ��������ǰ��Դ��·��
gofmt -w src

go install test_hello

export GOPATH="$OLD_GO_PATH"
export GOBIN="$OLD_GO_BIN"