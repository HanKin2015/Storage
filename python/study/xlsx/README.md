openpyxl：用于读取和写入Excel 2010 xlsx/xlsm/xltx/xltm文件的Python库。它支持Excel文件的所有基本操作，如读取单元格、写入单元格、合并单元格、设置单元格格式等。此外，openpyxl还支持图表、图像和公式等高级功能。
NumPy：用于数值计算和科学计算的Python库。
Pandas：用于数据分析和处理的Python库。
Matplotlib：用于绘制图表和可视化数据的Python库。
TensorFlow：用于机器学习和深度学习的Python库。
Scikit-learn：用于机器学习和数据挖掘的Python库。
PyTorch：用于机器学习和深度学习的Python库。
OpenCV：用于计算机视觉和图像处理的C++库。
Qt：用于图形用户界面开发的C++库。
Boost：用于C++编程的库，提供了许多常用的工具和算法。
JavaFX：用于Java图形用户界面开发的库。

这只是一小部分常用的库，还有很多其他的库可以使用，具体取决于你的需求和编程语言。


通过对比openpyxl和pandas，发现还是pandas好用。

## openpyxl的缺点
当我的表格是使用ctrl+A，ctrl+C，然后ctrl+V拷贝的数据，然后表格的数据大小统计就是巨大的，如1048554 10，但是pandas没有这种情况。
另外openpyxl不能识别第一行的列名，只能通过ABCDEF来进行遍历，或者使用12345遍历行，另外使用iter_cols或者iter_rows。

今天发现pip show numpy并没有发现库有多大，可能使用打包成exe文件会导致exe文件过大。

还有就是import导入openpyxl会慢几秒中，大约会卡住3.6秒左右。
```
import openpyxl
import time

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()
    
    import openpyxl

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))

(base) D:\Users\User\Desktop>python k.py
******** starting ********
process spend 3.741 s.
```
发现一个有趣的地方，如果在前面导入了openpyxl后，后面再导入就不会消耗时间了。
