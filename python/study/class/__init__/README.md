## 1、由于加了application路径__init__.py文件直接运行失败
```
(base) D:\Github\Storage\python\study\class\__init__\application>python __init__.py
Traceback (most recent call last):
  File "__init__.py", line 1, in <module>
    from application.settings import div
ModuleNotFoundError: No module named 'application'
```

## 2、可以发现__init__.py文件是默认被导入了
Pycharm创建相关的项目时，常常会看到 __init__.py，当你使用某些编辑器创建 Python Package 的时候，它也会自动给你生成一个 __init__.py 文件，那么__init__.py的用途是什么呢？

我们知道， Python 中的包是可以包含多个 py 模块的，我们可以在不同的地方通过包名区分使用这些模块。其实在 Python3.2 版本之前，定义的 Package 下面一定要有 __init__.py 文件，这样 Python 才知道它是一个 Package，才可以寻找到相关模块的路径从而被 import。而在 Python3.2 之后的版本就不需要再额外的去专门创建一个 __init__.py 来告诉 Python 它是一个 Package 了，因为现在创建的包叫 Namespace package， Python 可以自动搜寻 Package 路径，哪怕你的父包路径发生了改变，你在下次导入的时候， Python 还是会自动重新搜索包路径。

另外，__init__.py 会在 import 的时候被执行，虽然空的 __init__.py 在 Python 新版本中已经不需要你额外去定义了，因为就算你不定义 init， Python 也知道你导入的包路径，但是如果你想要做一些初始化操作当然，例如我们想预先导入相关的模块，那么定义 __init__.py 还是很有必要的。