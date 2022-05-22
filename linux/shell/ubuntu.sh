#!/bin/bash
set -e

#code_name=$(lsb_release -c |awk '{print $2}')
code_name="xenial"
if [ "$code_name" = "" ]; then
  echo "Failed!"
  exit 1
fi

cp /etc/apt/sources.list /etc/apt/sources.list.bak

echo "/etc/apt/sources.list  was bakup to /etc/apt/sources.list.bak"

wget http://mirrors.qinghua.org/assistants/ubuntu/sources.list -O /etc/apt/sources.list

sed -i "s/CODE_NAME/${code_name}/" /etc/apt/sources.list

apt update || apt-get update
