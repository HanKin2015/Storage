FROM debian:jessie
MAINTAINER tangjun "hankin@hello.com"
EXPOSE 22

ENV DEBIAN_FRONTEND noninteractive
ENV USER root
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_CTYPE en_US.UTF-8
ENV LC_ALL C.UTF-8

CMD sudo service ssh start && sleep infinity
RUN useradd --create-home --no-log-init --shell /bin/bash ubuntu \
&& dpkg --add-architecture amd64 \
&& echo > /etc/apt/sources.list \
&& sed -i "$ a deb http://aliyun:880/debian buster main contrib non-free" /etc/apt/sources.list \
&& apt-get update && apt-get install -y --force-yes apt-utils apt-transport-https ca-certificates locales openssh-server \
&& locale-gen en_US.UTF-8 && localedef -c -f UTF-8 -i en_US en_US.utf8 \
&& mkdir -p /root/.ssh/ && ssh-keygen -q -t rsa -C "hankin@hello.com" -b 4096 -f /root/.ssh/id_rsa -P "" && cat /root/.ssh/id_rsa.pub

RUN apt-get update \
&& apt-get install -y --force-yes --no-install-recommends \
autoconf bash-completion bc bison binfmt-support dialog \
build-essential chrpath cmake colordiff command-not-found cpio \
crudini curl device-tree-compiler devscripts dh-exec dh-make diffstat \
dos2unix dosfstools fakeroot flex g++ git glibc-doc iputils-ping \
jq less libtool locate lsof make automake man-db manpages-dev mtools vim \
pkg-kde-tools p7zip-full qemu-user-static rsync silversearcher-ag \
socat subversion sudo tclsh texinfo tree unzip wget xterm xz-utils zip \
apache2 apt-mirror live-build liblz4-tool net-tools \
nasm multiarch-support qt4-linguist-tools qt4-qmake libqt4-dev-bin 

# 配置ssh秘钥
RUN wget http://aliyun:8000/Sangfor2/1-%E4%B8%AA%E4%BA%BA%E7%9B%AE%E5%BD%95/sign/id_rsa.pub -O /root/.ssh/id_rsa.pub
RUN wget http://aliyun:8000/Sangfor2/1-%E4%B8%AA%E4%BA%BA%E7%9B%AE%E5%BD%95/sign/id_rsa -O /root/.ssh/id_rsa
RUN chmod 600 /root/.ssh/id_rsa && chmod 644 /root/.ssh/id_rsa.pub

RUN apt-get update && apt-get install -y --force-yes libqt4-dev:amd64 \
libqtgui4:amd64 libqt4-network:amd64 libqtcore4:amd64 libqtwebkit-dev:amd64 \
libudev-dev:amd64 libcurl4-openssl-dev:amd64 \
libxrandr-dev:amd64 libasound2-dev:amd64 \
libpulse-dev:amd64 libxinerama-dev:amd64 libbz2-1.0:amd64

RUN mkdir -p /android /share /root/ubuntu \
&& echo "ubuntu ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/ubuntu \
&& echo "root:123456" | chpasswd && echo "ubuntu:ubuntu" | chpasswd \
&& sed -i "$ a source /android/customrc 2>/dev/null" /root/.bashrc \
&& sed -i "$ a set ts=4" /etc/vim/vimrc \
&& sed -i "$ a set fileencodings=ucs-bom,utf-8,gb2312,utf-16,gbk,big5,gb18030,latin1" /etc/vim/vimrc \
&& sed -i "$ a set shiftwidth=4" /etc/vim/vimrc \
&& sed -i "$ a UseDNS no" /etc/ssh/sshd_config \
&& sed -i "$ a GSSAPIAuthentication no" /etc/ssh/sshd_config \
&& sed -i "$ a \    StrictHostKeyChecking no" /etc/ssh/ssh_config \
&& chown -R 1000:1000 /root/ubuntu /android /share

# 增加单测插桩依赖库
RUN wget http://aliyun:8000/Sangfor/Linux%E5%AE%89%E8%A3%85%E5%8C%85/addr_pri.h -O /usr/include/addr_pri.h
RUN wget http://aliyun:8000/Sangfor/Linux%E5%AE%89%E8%A3%85%E5%8C%85/stub.h -O /usr/include/stub.h

WORKDIR /root/ubuntu
USER root

# 拷贝依赖包到容器中
COPY docker_file/packages/nasm_2.15.05-1_amd64.deb /docker_build/packages/nasm_2.15.05-1_amd64.deb

# nasm依赖包安装
RUN dpkg -i /docker_build/packages/nasm_2.15.05-1_amd64.deb
RUN echo "nasm-2.15.05 installed"

# 需要cmake升级3.26.2
COPY docker_file/packages/cmake-3.26.2.tar.gz /docker_build/packages/cmake-3.26.2.tar.gz
RUN tar -xzvf /docker_build/packages/cmake-3.26.2.tar.gz \
	&& cd cmake-3.26.2 \
	&& ./bootstrap -- -DCMAKE_USE_OPENSSL=OFF\
	&& make -j$(nproc) && sudo make install

# x86默认路径在 /usr/local
COPY docker_file/packages/gcc-8.1.0-bin-x86-tar.gz /docker_build/packages/gcc-8.1.0-bin-x86-tar.gz
RUN tar -xzvf /docker_build/packages/gcc-8.1.0-bin-x86-tar.gz  -C /usr/local/

# 判断/etc/profile文件中是否存在gcc-8.1.0变量字段,g++-8.1.0为特意修改
RUN grep -q "gcc-8.1.0" /etc/profile || \ 
    echo 'export PATH="/usr/local/gcc-8.1.0/bin:${PATH}"' >> /etc/profile && \ 
    echo 'export CXX="/usr/local/gcc-8.1.0/bin/g++-8.1.0"' >> /etc/profile && \ 
    echo 'export CC="/usr/local/gcc-8.1.0/bin/gcc-8.1.0"' >> /etc/profile && \
    echo 'ln -sf /usr/local/gcc-8.1.0/bin/gcc-8.1.0 /usr/bin/gcc' >> /etc/profile && \
    echo 'ln -sf /usr/local/gcc-8.1.0/bin/g++-8.1.0 /usr/bin/g++' >> /etc/profile && \
    echo 'ln -sf /usr/local/gcc-8.1.0/lib64/libstdc++.so.6.0.25 /usr/lib/x86_64-linux-gnu/libstdc++.so.6' >> /etc/profile && \
    echo 'export LIBRARY_PATH="/usr/lib/x86_64-linux-gnu:${LIBRARY_PATH}"' >> /etc/profile && \
    echo 'export CPATH="/usr/include/x86_64-linux-gnu:${CPATH}"' >> /etc/profile
RUN . /etc/profile

RUN ln -s make /usr/bin/gmake
