## 1、源码转deb包
操作记录见：D:\Github\GitBook\gitbook\Linux\deb_package.md

## 2、文件说明
源码：e1000e-3.8.4.tar.gz

使用dpkg方法创建deb包：dh_make_e1000e-3.8.4-1_amd64.deb

使用checkinstall方法创建deb包：checkinstall_e1000e-3.8.4.deb

## 3、打包成deb安装包
dpkg-deb -b hello_deb/ hello-1.0-linux.deb

