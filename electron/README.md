# electron入门

学习教程：https://www.electronjs.org/zh/docs/latest/tutorial/tutorial-first-app

安装node.js环境请参考：D:\Github\GitBook\gitbook\Tools\gitbook.md

## 1、简介
Electron是由Github开发，用HTML，CSS和JavaScript来构建跨平台桌面应用程序的一个开源库。 Electron通过将Chromium和Node.js合并到同一个运行时环境中，并将其打包为Mac，Windows和Linux系统下的应用来实现这一目的。

## 2、实战
由于本地上库的项目文件夹中删除了node_modules文件夹，因此需要运行测试则需要一下几步：
```
打开cmd窗口，然后执行以下命令，会在项目文件夹中生成node_modules文件夹
npm install electron --save-dev
npm run start

preload项目运行结果：
Hello from Electron renderer!
👋

欢迎来到 Electron 👋

本应用正在使用 Chrome (v91.0.4472.164), Node.js (v14.16.0), 和 Electron (v13.6.9)
```

https://blog.csdn.net/Naisu_kun/article/details/120664068
https://zhuanlan.zhihu.com/p/268280901

## 3、桌面应用技术栈对比
https://www.zhihu.com/question/322125431

学习教程：https://www.zhihu.com/people/michael-jean/posts