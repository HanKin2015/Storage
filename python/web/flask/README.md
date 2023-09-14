# Flask框架最基本的使用
https://zhuanlan.zhihu.com/p/637789895
https://zhuanlan.zhihu.com/p/622394487

## 1、Flask框架介绍
Flask诞生于2010年，是Armin ronacher（阿明·罗纳彻）用 Python 语言基于 Werkzeug 工具箱编写的轻量级Web开发框架。

Flask 本身相当于一个内核，其他几乎所有的功能都要用到扩展（邮件扩展Flask-Mail，用户认证Flask-Login，数据库Flask-SQLAlchemy），都需要用第三方的扩展来实现。比如可以用 Flask 扩展加入ORM、窗体验证工具，文件上传、身份验证等。Flask 没有默认使用的数据库，你可以选择 MySQL，也可以用 NoSQL。

flask的 WSGI 工具箱采用 Werkzeug（路由模块），模板引擎则使用 Jinja2。Itsdangrous（token加密模块），Click(终端命令管理工具)，flask内核本身，这5个核心模块组成 Flask 框架。

官方文档：https://flask.palletsprojects.com/en/2.0.x/

中文文档：https://dormousehole.readthedocs.io

Flask常用第三方扩展包：
Flask-SQLAlchemy：操作数据库,ORM；
Flask-script：终端脚本工具，脚手架； ( 淘汰，官方内置脚手架：Click)
Flask-migrate：管理迁移数据库；
Flask-Session：Session存储方式指定；
Flask-Mail：邮件；
Flask-Login：认证用户状态；（django内置Auth模块，用于实现用户登录退出，）
Flask-OpenID：认证, OAuth；（三方授权，）
Flask-RESTful：开发REST API的工具；
Flask JSON-RPC: 开发json-rpc远程服务[过程]调用
Flask-Bable：提供国际化和本地化支持，翻译；
Flask-Moment：本地化日期和时间
Flask-Admin：简单而可扩展的管理接口的框架
Flask-Bootstrap：集成前端Twitter Bootstrap框架（前后端分离，除了admin站点，基本不用这玩意）
Flask-WTF：表单生成模块；（前后端分离，csrf集成在这个模块中，除了admin站点，基本不用这玩意）
Flask-Marshmallow：序列化（类似djangorestframework的序列化器）
可以通过 https://pypi.org/search/?c=Framework+%3A%3A+Flask 查看更多flask官方推荐的扩展

## 2、flask和开发工具pychram安装
pip install Flask

pychram请到官网下载。（专业版最好）

## 3、项目配置之debug模式
新建项目的时候记得选择flask。
```
# 运行代码
if __name__ == '__main__':
    app.run(debug=True)
```

## 4、修改host
如果想让在同一个网络下的其他设备可以访问的话，需要修改为0.0.0.0或者也可以使用 --host=你的ipaddress也行。
然后就可以在另外一台电脑进行网页访问了。

## 5、修改端口号
就是修改项目运行的端口号。
--host=0.0.0.0 --port=5001

## 6、后面的教程
当前还是小白，后面的代码似乎不完整，运行不起来，后面学会了再来看看。
原来是教程中部分代码有单词写错误。

## 7、已明白蓝图的作用
- 首先蓝图函数是不能有参数的
- 蓝图函数是提供给前端界面的接口函数
- 蓝图调用python写的后端函数，相当于是中间连接的桥梁
- 蓝图需要注册

