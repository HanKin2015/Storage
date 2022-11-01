# DataFrame中的groupby函数

## 1、groupby的函数定义
```
DataFrame.groupby(by=None, axis=0, level=None, as_index=True, sort=True, group_keys=True, squeeze=False, **kwargs)
```
by :接收映射、函数、标签或标签列表；用于确定聚合的组。
axis : 接收 0/1；用于表示沿行(0)或列(1)分割。
level : 接收int、级别名称或序列，默认为None；如果轴是一个多索引(层次化)，则按一个或多个特定级别分组。
as_index：接收布尔值，默认Ture；Ture则返回以组标签为索引的对象，False则不以组标签为索引。
其他的参数解释就看文档吧：链接：[pandas.DataFrame.groupby 介绍文档](https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.DataFrame.groupby.html)

## 2、解决groupby.sum() 后层级索引levels上移的问题
代码见：
虽然是 DataFrame 的格式，但是若需要与其他表匹配的时候，这个格式就有些麻烦了。匹配数据时，我们需要的数据格式是：列名都在第一行，数据行中也不能有 Gender 列这样的合并单元格。因此，我们需要做一些调整，将 as_index 改为 False ，默认是 Ture 。

## 3、解决groupby.apply() 后层级索引levels上移的问题
在所见 2 中我们知道，使用参数 as_index 就可使 groupby 的结果不以组标签为索引，但是后来在使用 groupby.apply() 时发现，as_index 参数失去了效果。

解决办法： 加一句df_apply_index = df_apply.reset_index()

## 4、groupby函数的分组结果保存成DataFrame
所见 1 中的输出三，明显是  Series ,我们需要将其转化为 DataFrame 格式的数据。








