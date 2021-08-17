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


#ע��bashrc ��ϵͳ�����û���Ч��profile �Ե�ǰ�û���Ч��
#���������� GOPATH��PATH��GOROOT��
#GOROOT ���� go �İ�װ·����
#GOPATH ����go�Ĺ���Ŀ¼��
#PATH��go��װ·���µ�binĿ¼��
export GOROOT="/usr/local/go"
export GOPATH="/go"
export PATH=$PATH:/usr/local/go/bin
