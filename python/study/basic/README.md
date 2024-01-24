# 一些基础学习

## 1、with 语句
参考：https://blog.csdn.net/knighthood2001/article/details/120624571
demo：D:\Github\Storage\python\study\basic\with_example.py

我们在日常读取文件资源时，经常会用到with open() as f:的句子。

但是使用with语句的时候是需要条件的，任何对象，只要正确实现了上下文管理，就可以使用with语句，实现上下文管理是通过__enter__和__exit__这两个方法实现的。

## 2、对于if __name__ == '__main__':语句
在python文件中有没有这个影响不大，唯一的影响就是如果你的脚本被设计为既可以独立运行，也可以作为模块被导入，那么就需要使用这个语句将可执行代码放在里面。如果仅仅自身使用就无关紧要了。






